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
    // ���� Ÿ�� �ؽ�ó
    //

    // ���� Ÿ�� �ؽ�ó ����ü ����
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

    // ���� Ÿ�� �ؽ�ó ����
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateTexture2D(
            &textureDesc, nullptr, _rtTextures[i].ReleaseAndGetAddressOf());
    }

    //
    // ���� Ÿ�� ��
    //

    // ���� Ÿ�� �� ����ü ����
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    renderTargetViewDesc.Format = textureDesc.Format; // DXGI_FORMAT_R32G32B32A32_FLOAT
    renderTargetViewDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

    // ���� Ÿ�� �� ����
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateRenderTargetView(_rtTextures[i].Get(),
            &renderTargetViewDesc,
            _rtViews[i].GetAddressOf());
    }

    //
    // ���̴� ���ҽ� ��
    //

    // ���̴� ���ҽ� �� ����ü ����
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    shaderResourceViewDesc.Format        = textureDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels       = 1;

    // ���̴� ���ҽ� �� ����
    for (unsigned i = 0; i < bufferCount; i++)
    {
        device->CreateShaderResourceView(_rtTextures[i].Get(),
            &shaderResourceViewDesc,
            _srViews[i].ReleaseAndGetAddressOf());
    }

    //
    // ���� ���ٽ� ���� ��
    //

    // ���� ������ ����ü ����
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

    // ���� ���� ����
    device->CreateTexture2D(&depthStencilDesc,
        nullptr,
        _dsBuffer.GetAddressOf()); // ����/���ٽ� ���� ��ȯ

    // ���� ���ٽ� �� ����ü �ʱ�ȭ
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
    depthStencilViewDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // ���� ���ٽ� �� ����
    device->CreateDepthStencilView(
        _dsBuffer.Get(), &depthStencilViewDesc, _dsView.ReleaseAndGetAddressOf());

    //
    // �� ��Ʈ
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
    // ���� Ÿ�� �� �迭�� ���� ���ٽ� ���۸� �ƿ�ǲ ������ ���������ο� ���ε�
    deviceContext->OMSetRenderTargets(
        bufferCount, _rtViews.data()->GetAddressOf(), _dsView.Get());

    // �� ��Ʈ ����
    deviceContext->RSSetViewports(1, &_viewPort);
}

void DeferredBuffers::ClearRenderTargets(ID3D11DeviceContext* deviceContext)
{
    // ���۸� ���� �� ����
    float color[4] = { 0.f, 0.f, 0.f, 0.f };

    // ���� Ÿ�� ���� �����
    for ( auto& view : _rtViews)
    {
        deviceContext->ClearRenderTargetView(view.Get(), color);
    }

    // ���� ���� �����
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