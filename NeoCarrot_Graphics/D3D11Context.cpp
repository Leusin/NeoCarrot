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
    /// ����̽��� DC(device context) ����
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

    // ���� ��� ���� ����/���ٽ� ���۸� ����
    _renderTargetView.Reset();

    // ���� ü�ΰ� ���� Ÿ�� �缳��
    _swapChain->ResizeBuffers(1, clientWidth, clientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ID3D11Texture2D* backBuffer;

    /// ���� ��� ���� ����

    //��ȯ �罽 ������ ���

    _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

    // ���� Ÿ�� �� ����
    assert(backBuffer != 0);
    _d3dDevice->CreateRenderTargetView(backBuffer, 0, _renderTargetView.GetAddressOf());
    assert(_renderTargetView);

    if (backBuffer)
    {
        backBuffer->Release();
    }

    /// ����/���ٽ� ���� ����

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = clientWidth;                   // �ؽ�ó �ʺ�
    depthStencilDesc.Height    = clientHeight;                  // �ؽ�ó ����
    depthStencilDesc.MipLevels = 1;                             // �ؽ�ó�� Minmap ���� ��
    depthStencilDesc.ArraySize = 1;                             // �ؽ�ó �迭�� �ؽ�ó ��
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // ����

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;      // �ؽ�ó�� �а� ���� ��� �ĺ�
    depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL; // ������������ ���ε� �÷���
    depthStencilDesc.CPUAccessFlags = 0; // CPU ���� ��� ���� �÷��� (������� �ʾ�, 0)
    depthStencilDesc.MiscFlags      = 0; // ��Ÿ ���ҽ� �ɼ� �÷���

    _d3dDevice->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer); // ����/���ٽ� ���� ��ȯ
    assert(_depthStencilBuffer);

    _d3dDevice->CreateDepthStencilView(_depthStencilBuffer.Get(), 0, &_depthStencilView); // ����/���ڽ� �� ��ȯ
    assert(_depthStencilView);

    /// ����� ��� ���ձ� �ܰ迡 ����
    // ���� Ÿ�� ��� ����/���ٽ� �並 ���������ξּ� ���´�

    _d3dDiviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
    assert(_renderTargetView);

    /// ����Ʈ ����
    _screenViewport->TopLeftX = 0;
    _screenViewport->TopLeftY = 0;
    _screenViewport->Width    = static_cast<float>(clientWidth);
    _screenViewport->Height   = static_cast<float>(clientHeight);
    _screenViewport->MinDepth = 0.0f; // �ּ� ���� ����
    _screenViewport->MaxDepth = 1.0f; // �ִ� ���� ����

    _d3dDiviceContext->RSSetViewports(1, _screenViewport);
}

void graphics::D3D11Context::BeginRender()
{
    // �ĸ� ���۸� ������ ������ ����
    DiviceContext()->ClearRenderTargetView(RenderTargetView(), reinterpret_cast<const float*>(&myColor::Carrot));

    //���̹��۸� 1.0f, ���ٽ� ���۸� 0 ���� ����
    DiviceContext()->ClearDepthStencilView(DepthStencilView(), /*D3D11_CLEAR_DEPTH*/ 1 | /*D3D11_CLEAR_STENCIL*/ 2, 1.0f, 0);
}

void graphics::D3D11Context::EndRender()
{
    // �ĸ� ���� ����
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

    UINT _4xMsaaQality; // 4XMSAA��ǰ������
    _d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQality);
    assert(_4xMsaaQality > 0); // ȯ�� ���ذ��� 0���� ũ���� ����
}

void graphics::D3D11Context::CreateSwapChain(HWND hWnd, int w, int h)
{
    /// ��ȯ �罽 ����

    DXGI_SWAP_CHAIN_DESC swapChain;
    swapChain.BufferDesc.Width                   = w;
    swapChain.BufferDesc.Height                  = h;
    swapChain.BufferDesc.RefreshRate.Numerator   = 60;                         // ���÷��� �츣�� ����
    swapChain.BufferDesc.RefreshRate.Denominator = 1;                          // ���÷��� �츣�� �и�
    swapChain.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM; // �ĸ� ���� �ȼ� ����
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

    /// ��ȯ �罽 ����

    // ����ü�ο� �ʿ��� ��ü
    IDXGIDevice* dxgiDevice{nullptr};
    _d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* dxgiAdapter{nullptr};
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

    IDXGIFactory* dxgiFactory{nullptr};
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    // ���� ü�� ����
    dxgiFactory->CreateSwapChain(_d3dDevice.Get(), &swapChain, _swapChain.GetAddressOf());

    assert(_swapChain.Get());

    // ����ü�ο� �ʿ��� ��ü ����
    if (dxgiDevice)
        dxgiDevice->Release();
    if (dxgiAdapter)
        dxgiAdapter->Release();
    if (dxgiFactory)
        dxgiFactory->Release();
}