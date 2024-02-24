#include "DeferredBuffers.h"

namespace graphics
{

DeferredBuffers::DeferredBuffers()
{
}

DeferredBuffers::DeferredBuffers(const DeferredBuffers&)
{
}

DeferredBuffers::~DeferredBuffers()
{
}

void DeferredBuffers::Initialize(ID3D11Device* device, int width, int height)
{
    //
    // 랜더 타겟 텍스처
    //

    // 랜더 타겟 텍스처 구조체 설정
    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width            = width;
    textureDesc.Height           = height;
    textureDesc.MipLevels        = 1;
    textureDesc.ArraySize        = 1;
    textureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage            = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags      = 0;

    // 랜더 타겟 텍스처 생성
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateTexture2D(
            &textureDesc, nullptr, _rtTextures[i].ReleaseAndGetAddressOf());
    }

    //
    // 랜더 타겟 뷰
    //

    // 랜더 타겟 뷰 구조체 설정
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = textureDesc.Format; // DXGI_FORMAT_R32G32B32A32_FLOAT
    renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

    // 랜더 타겟 뷰 생성
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateRenderTargetView(_rtTextures[i].Get(),
            &renderTargetViewDesc,
            _rtViews[i].GetAddressOf());
    }

    //
    // 셰이더 리소스 뷰
    //

    // 셰이더 리소스 뷰 구조체 설정
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format        = textureDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels       = 1;

    // 셰이더 리소스 뷰 생성
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateShaderResourceView(_rtTextures[i].Get(),
            &shaderResourceViewDesc,
            _srViews[i].ReleaseAndGetAddressOf());
    }

    //
    // 뎁스 스텐실 버퍼 뷰
    //

    // 뎁스 버퍼의 구조체 설정
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.Width              = width;
    depthStencilDesc.Height             = height;
    depthStencilDesc.MipLevels          = 1;
    depthStencilDesc.ArraySize          = 1;
    depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
    depthStencilDesc.CPUAccessFlags     = 0;
    depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.MiscFlags          = 0;

    // 뎁스 버퍼 생성
    device->CreateTexture2D(&depthStencilDesc,
        nullptr,
        _dsBuffer.GetAddressOf()); // 깊이/스텐실 버퍼 반환

    // 뎁스 스텐실 뷰 구조체 초기화
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
    depthStencilViewDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // 뎁스 스텐실 뷰 생성
    device->CreateDepthStencilView(
        _dsBuffer.Get(), &depthStencilViewDesc, _dsView.ReleaseAndGetAddressOf());

    //
    // 뷰 포트
    //

    D3D11_VIEWPORT screenViewport;

    screenViewport.TopLeftX = 0;
    screenViewport.TopLeftY = 0;
    screenViewport.Width    = static_cast<float>(width);
    screenViewport.Height   = static_cast<float>(height);
    screenViewport.MinDepth = 0.0f;
    screenViewport.MaxDepth = 1.0f;
}

void DeferredBuffers::Finalize()
{
    _dsView->Release();
    _dsBuffer->Release();
    /*
    for (auto& view : _srViews)
        if (view.Get() != nullptr) view->Release();

    for (auto& view : _rtViews)
        if (view.Get() != nullptr) view->Release();

    for (auto& view : _rtTextures)
        if (view.Get() != nullptr) view->Release();
    */
}

void DeferredBuffers::SetRenderTargets(ID3D11DeviceContext* deviceContext)
{
    // 랜더 타깃 뷰 배열와 뎁스 스텐실 버퍼를 아웃풋 랜더링 파이프라인에 바인딩
    deviceContext->OMSetRenderTargets(
        bufferCount, _rtViews.data()->GetAddressOf(), _dsView.Get());

    // 뷰 포트 설정
    deviceContext->RSSetViewports(1, &_viewPort);
}

void DeferredBuffers::ClearRenderTargets(ID3D11DeviceContext* deviceContext)
{
    // 버퍼를 지울 색 설정
    float color[4] = { 0.f, 0.f, 0.f, 0.f };

    // 랜더 타겟 버퍼 지우기
    for ( auto& view : _rtViews)
    {
        deviceContext->ClearRenderTargetView(view.Get(), color);
    }

    // 뎁스 버퍼 지우기
    deviceContext->ClearDepthStencilView(_dsView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);
}

ID3D11ShaderResourceView* DeferredBuffers::GetShaderResourceView(int view)
{
    if (_srViews.empty() == true || view >= bufferCount || view < 0)
    {
        return nullptr;
    }

    return _srViews[view].Get();
}

} // namespace graphics