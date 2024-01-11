#include "D3D11Context.h"

#include "DXTKFont.h"
#include "MyColor.h"

#include <d3d11.h>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

graphics::D3D11Context::D3D11Context(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight) :
_screenViewport(new D3D11_VIEWPORT())
{
    /// 디바이스와 DC(device context) 생성
    CreateDeviceContext();
    CreateSwapChain(hWnd, clientWidth, clientHeight);
    //ZeroMemory(&_screenViewport, sizeof(D3D11_VIEWPORT));
    OnResize(clientWidth, clientHeight);

#ifdef _DEBUG
    std::cout << "\tD3D11Context Constructed\n";
#endif // _DEBUG
}

graphics::D3D11Context::~D3D11Context()
{
    if (_screenViewport)
    {
        delete _screenViewport;
    }

    if (_d3dDiviceContext)
    {
        _d3dDiviceContext->ClearState();
        _d3dDiviceContext->Flush();
    }
}

ID3D11Device* graphics::D3D11Context::Divice()
{
    return _d3dDevice.Get();
}

ID3D11DeviceContext* graphics::D3D11Context::DiviceContext()
{
    return _d3dDiviceContext.Get();
}

IDXGISwapChain* graphics::D3D11Context::SwapChain()
{
    return _swapChain.Get();
}

ID3D11Texture2D* graphics::D3D11Context::DethStencilBuffer()
{
    return _depthStencilBuffer.Get();
}

ID3D11RenderTargetView* graphics::D3D11Context::RenderTargetView()
{
    return _renderTargetView.Get();
}

ID3D11DepthStencilView* graphics::D3D11Context::DepthStencilView()
{
    return _depthStencilView.Get();
}

void graphics::D3D11Context::OnResize(int clientWidth, int clientHeight)
{
    assert(_d3dDiviceContext.Get());
    assert(_d3dDevice.Get());
    assert(_swapChain.Get());

    // 이전 뷰와 이전 깊이/스텐실 버퍼를 해제
    _renderTargetView.Reset();

    // 스왑 체인과 랜더 타겟 재설정
    _swapChain->ResizeBuffers(1, clientWidth, clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ID3D11Texture2D* backBuffer;

    /// 랜더 대상 뷰의 생성

    //교환 사슬 포인터 얻기

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

    // 랜더 타겟 뷰 생성
    assert(backBuffer != 0);
    _d3dDevice->CreateRenderTargetView(backBuffer, 0, _renderTargetView.GetAddressOf());
    assert(_renderTargetView);

    if (backBuffer)
    {
        backBuffer->Release();
    }

    /// 깊이/스텐실 버퍼 생성

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = clientWidth;                   // 텍스처 너비
    depthStencilDesc.Height    = clientHeight;                  // 텍스처 높이
    depthStencilDesc.MipLevels = 1;                             // 텍스처의 Minmap 수준 수
    depthStencilDesc.ArraySize = 1;                             // 텍스처 배열의 텍스처 수
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // 형식

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;      // 텍스처를 읽고 쓰는 방법 식별
    depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL; // 파이프라인의 바인딩 플래그
    depthStencilDesc.CPUAccessFlags = 0; // CPU 접근 허용 유형 플래그 (사용하지 않아, 0)
    depthStencilDesc.MiscFlags      = 0; // 기타 리소스 옵션 플래그

    _d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer); // 깊이/스텐실 버퍼 반환
    assert(_depthStencilBuffer);

    _d3dDevice->CreateDepthStencilView(_depthStencilBuffer.Get(), 0, &_depthStencilView); // 깊이/스텔실 뷰 반환
    assert(_depthStencilView);

    /// 뷰들을 출력 병합기 단계에 묶기
    // 랜더 타깃 뷰와 깊이/스텐실 뷰를 파이프라인애서 묶는다

    _d3dDiviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
    assert(_renderTargetView);

    /// 뷰포트 설정
    _screenViewport->TopLeftX = 0;
    _screenViewport->TopLeftY = 0;
    _screenViewport->Width    = static_cast<float>(clientWidth);
    _screenViewport->Height   = static_cast<float>(clientHeight);
    _screenViewport->MinDepth = 0.0f; // 최소 깊이 버퍼
    _screenViewport->MaxDepth = 1.0f; // 최대 깊이 버퍼

    _d3dDiviceContext->RSSetViewports(1, _screenViewport);
}

void graphics::D3D11Context::BeginRender()
{
    // 후면 버퍼를 지정돤 색으로 지움
    DiviceContext()->ClearRenderTargetView(RenderTargetView(), reinterpret_cast<const float*>(&myColor::Carrot));

    //깊이버퍼를 1.0f, 스텐실 버퍼를 0 으로 지움
    DiviceContext()->ClearDepthStencilView(DepthStencilView(), /*D3D11_CLEAR_DEPTH*/ 1 | /*D3D11_CLEAR_STENCIL*/ 2, 1.0f, 0);
}

void graphics::D3D11Context::EndRender()
{
    // 후면 버퍼 제시
    _swapChain->Present(0, 0);
}

void graphics::D3D11Context::CreateDeviceContext()
{
    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE d3dDriverType{D3D_DRIVER_TYPE_HARDWARE};

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT           hr = D3D11CreateDevice(0,
                                   d3dDriverType,
                                   0,
                                   createDeviceFlags,
                                   0,
                                   0,
                                   D3D11_SDK_VERSION,
                                   _d3dDevice.GetAddressOf(),
                                   &featureLevel,
                                   _d3dDiviceContext.GetAddressOf());

    assert(_d3dDevice.Get());
    assert(_d3dDiviceContext.Get());

    if (FAILED(hr))
    {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return;
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
        return;
    }

    UINT _4xMsaaQality; // 4XMSAA의품질수준
    _d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQality);
    assert(_4xMsaaQality > 0); // 환된 수준값이 0보다 크도록 강제
}

void graphics::D3D11Context::CreateSwapChain(HWND hWnd, int w, int h)
{
    /// 교환 사슬 설정

    DXGI_SWAP_CHAIN_DESC swapChain;
    swapChain.BufferDesc.Width                   = w;
    swapChain.BufferDesc.Height                  = h;
    swapChain.BufferDesc.RefreshRate.Numerator   = 60;                         // 디스플레이 헤르츠 분자
    swapChain.BufferDesc.RefreshRate.Denominator = 1;                          // 디스플레이 헤르츠 분모
    swapChain.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM; // 후면 버퍼 픽셀 형식
    swapChain.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChain.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

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
    IDXGIDevice* dxgiDevice{nullptr};
    _d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* dxgiAdapter{nullptr};
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

    IDXGIFactory* dxgiFactory{nullptr};
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    // 스왑 체인 생성
    dxgiFactory->CreateSwapChain(_d3dDevice.Get(), &swapChain, _swapChain.GetAddressOf());

    assert(_swapChain.Get());

    // 스왑체인에 필요한 객체 정리
    if (dxgiDevice)
        dxgiDevice->Release();
    if (dxgiAdapter)
        dxgiAdapter->Release();
    if (dxgiFactory)
        dxgiFactory->Release();
}