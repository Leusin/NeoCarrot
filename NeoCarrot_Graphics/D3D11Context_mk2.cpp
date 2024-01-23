/// 2024-01-15

#include "D3D11Context_mk2.h"

#include "Devices.h"
#include "RenderStates.h"
#include "ResourceView.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <cassert>

namespace graphics
{

D3D11Context_mk2::D3D11Context_mk2(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight)
    : _devices(std::make_unique<Devices>())
    , _resourceView(std::make_unique<ResourceView>())
    , _renderState(std::make_unique<RenderStates>(_devices->Device()))
{
    CreateSwapChain(hWnd, clientWidth, clientHeight);

    OnResize(clientWidth, clientHeight);

#ifdef _DEBUG
    std::cout << "\tD3D11Context_mk2 Constructed\n";
#endif // _DEBUG
}

D3D11Context_mk2::~D3D11Context_mk2()
{
}


ID3D11Device* D3D11Context_mk2::GetDevice() const
{
    return _devices->Device();
}

const Devices* D3D11Context_mk2::GetDevices() const
{
    return _devices.get();
}

ResourceView* D3D11Context_mk2::GetResourceView() const
{
    return _resourceView.get();
}

RenderStates* D3D11Context_mk2::GetRenderStates() const
{
    return _renderState.get();
}

void D3D11Context_mk2::CreateSwapChain(HWND hWnd, int width, int height)
{
    /// 교환 사슬 설정

    DXGI_SWAP_CHAIN_DESC swapChain;
    swapChain.BufferDesc.Width  = width;
    swapChain.BufferDesc.Height = height;
    swapChain.BufferDesc.RefreshRate.Numerator = 60; // 디스플레이 헤르츠 분자
    swapChain.BufferDesc.RefreshRate.Denominator = 1; // 디스플레이 헤르츠 분모
    swapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 후면 버퍼 픽셀 형식
    swapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapChain.SampleDesc.Count   = 1;
    swapChain.SampleDesc.Quality = 0;

    swapChain.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChain.BufferCount  = 1;
    swapChain.OutputWindow = hWnd;
    swapChain.Windowed     = true;
    swapChain.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    swapChain.Flags        = 0;

    /// 교환 사슬 생성

    // 스왑체인에 필요한 객체
    IDXGIDevice* dxgiDevice{ nullptr };
    _devices->Device()->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* dxgiAdapter{ nullptr };
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

    IDXGIFactory* dxgiFactory{ nullptr };
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    // 스왑 체인 생성
    dxgiFactory->CreateSwapChain(_devices->Device(),
                                 &swapChain,
                                 _swapChain.GetAddressOf());

    assert(_swapChain.Get());

    // 스왑체인에 필요한 객체 정리
    if (dxgiDevice)
        dxgiDevice->Release();
    if (dxgiAdapter)
        dxgiAdapter->Release();
    if (dxgiFactory)
        dxgiFactory->Release();
}

void D3D11Context_mk2::OnResize(int width, int height)
{
    // 이전 뷰와 이전 깊이/스텐실 버퍼를 해제
    _resourceView->renderTargetView.Reset();

    // 스왑 체인과 랜더 타겟 재설정
    _swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ID3D11Texture2D* backBuffer{ nullptr };

    /// 랜더 대상 뷰의 생성

    // 교환 사슬 포인터 얻기

    _swapChain->GetBuffer(0,
                          __uuidof(ID3D11Texture2D),
                          reinterpret_cast<void**>(&backBuffer));

    // 랜더 타겟 뷰 생성
    assert(backBuffer != 0);
    _devices->Device()
        ->CreateRenderTargetView(backBuffer,
                                 0,
                                 _resourceView->renderTargetView.GetAddressOf());
    assert(_resourceView->renderTargetView);

    if (backBuffer)
    {
        backBuffer->Release();
    }

    /// 깊이/스텐실 버퍼 생성
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = width;  // 텍스처 너비
    depthStencilDesc.Height    = height; // 텍스처 높이
    depthStencilDesc.MipLevels = 1;      // 텍스처의 Minmap 수준 수
    depthStencilDesc.ArraySize = 1;      // 텍스처 배열의 텍스처 수
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // 형식

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // 텍스처를 읽고 쓰는 방법 식별
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 파이프라인의 바인딩 플래그
    depthStencilDesc.CPUAccessFlags = 0; // CPU 접근 허용 유형 플래그 (사용하지 않아, 0)
    depthStencilDesc.MiscFlags = 0; // 기타 리소스 옵션 플래그


    _devices->Device()->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer); // 깊이/스텐실 버퍼 반환
    assert(_depthStencilBuffer);

    _devices->Device()->CreateDepthStencilView(_depthStencilBuffer.Get(),
                                               0,
                                               &_resourceView->depthStencilView); // 깊이/스텔실 뷰 반환
    assert(_resourceView->depthStencilView);

    /// 뷰들을 출력 병합기 단계에 묶기

    // 생성한 뎁스 스텐실 버퍼를 디바이스에 바인딩
    _devices->ImmediateContext()
        ->OMSetRenderTargets(1,
                             _resourceView->renderTargetView.GetAddressOf(),
                             _resourceView->depthStencilView.Get());

    assert(_resourceView->renderTargetView);

    /// 뷰포트 설정
    D3D11_VIEWPORT screenViewport;

    screenViewport.TopLeftX = 0;
    screenViewport.TopLeftY = 0;
    screenViewport.Width    = static_cast<float>(width);
    screenViewport.Height   = static_cast<float>(height);
    screenViewport.MinDepth = 0.0f; // 최소 깊이 버퍼
    screenViewport.MaxDepth = 1.0f; // 최대 깊이 버퍼

    _devices->ImmediateContext()->RSSetViewports(1, &screenViewport);
}

void D3D11Context_mk2::BeginRender(const float* color) const
{
    // 후면 버퍼를 지정돤 색으로 지움
    _devices->ImmediateContext()
        ->ClearRenderTargetView(_resourceView->renderTargetView.Get(), color);
    // 깊이버퍼를 1.0f, 스텐실 버퍼를 0 으로 지움
    _devices->ImmediateContext()
        ->ClearDepthStencilView(_resourceView->depthStencilView.Get(),
                                D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                1.0f,
                                0);
    _devices->ImmediateContext()
        ->OMSetDepthStencilState(_renderState->normalDSS.Get(),
                                 0); // 안하면 뒤의 것이 앞으로 그려짐)
}

void D3D11Context_mk2::EndRender() const
{
    // 후면 버퍼 제시
    _swapChain->Present(0, 0);
}

} // namespace graphics