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
    /// ��ȯ �罽 ����

    DXGI_SWAP_CHAIN_DESC swapChain;
    swapChain.BufferDesc.Width  = width;
    swapChain.BufferDesc.Height = height;
    swapChain.BufferDesc.RefreshRate.Numerator = 60; // ���÷��� �츣�� ����
    swapChain.BufferDesc.RefreshRate.Denominator = 1; // ���÷��� �츣�� �и�
    swapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �ĸ� ���� �ȼ� ����
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

    /// ��ȯ �罽 ����

    // ����ü�ο� �ʿ��� ��ü
    IDXGIDevice* dxgiDevice{ nullptr };
    _devices->Device()->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* dxgiAdapter{ nullptr };
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

    IDXGIFactory* dxgiFactory{ nullptr };
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    // ���� ü�� ����
    dxgiFactory->CreateSwapChain(_devices->Device(),
                                 &swapChain,
                                 _swapChain.GetAddressOf());

    assert(_swapChain.Get());

    // ����ü�ο� �ʿ��� ��ü ����
    if (dxgiDevice)
        dxgiDevice->Release();
    if (dxgiAdapter)
        dxgiAdapter->Release();
    if (dxgiFactory)
        dxgiFactory->Release();
}

void D3D11Context_mk2::OnResize(int width, int height)
{
    // ���� ��� ���� ����/���ٽ� ���۸� ����
    _resourceView->renderTargetView.Reset();

    // ���� ü�ΰ� ���� Ÿ�� �缳��
    _swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    ID3D11Texture2D* backBuffer{ nullptr };

    /// ���� ��� ���� ����

    // ��ȯ �罽 ������ ���

    _swapChain->GetBuffer(0,
                          __uuidof(ID3D11Texture2D),
                          reinterpret_cast<void**>(&backBuffer));

    // ���� Ÿ�� �� ����
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

    /// ����/���ٽ� ���� ����
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = width;  // �ؽ�ó �ʺ�
    depthStencilDesc.Height    = height; // �ؽ�ó ����
    depthStencilDesc.MipLevels = 1;      // �ؽ�ó�� Minmap ���� ��
    depthStencilDesc.ArraySize = 1;      // �ؽ�ó �迭�� �ؽ�ó ��
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // ����

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; // �ؽ�ó�� �а� ���� ��� �ĺ�
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // ������������ ���ε� �÷���
    depthStencilDesc.CPUAccessFlags = 0; // CPU ���� ��� ���� �÷��� (������� �ʾ�, 0)
    depthStencilDesc.MiscFlags = 0; // ��Ÿ ���ҽ� �ɼ� �÷���


    _devices->Device()->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer); // ����/���ٽ� ���� ��ȯ
    assert(_depthStencilBuffer);

    _devices->Device()->CreateDepthStencilView(_depthStencilBuffer.Get(),
                                               0,
                                               &_resourceView->depthStencilView); // ����/���ڽ� �� ��ȯ
    assert(_resourceView->depthStencilView);

    /// ����� ��� ���ձ� �ܰ迡 ����

    // ������ ���� ���ٽ� ���۸� ����̽��� ���ε�
    _devices->ImmediateContext()
        ->OMSetRenderTargets(1,
                             _resourceView->renderTargetView.GetAddressOf(),
                             _resourceView->depthStencilView.Get());

    assert(_resourceView->renderTargetView);

    /// ����Ʈ ����
    D3D11_VIEWPORT screenViewport;

    screenViewport.TopLeftX = 0;
    screenViewport.TopLeftY = 0;
    screenViewport.Width    = static_cast<float>(width);
    screenViewport.Height   = static_cast<float>(height);
    screenViewport.MinDepth = 0.0f; // �ּ� ���� ����
    screenViewport.MaxDepth = 1.0f; // �ִ� ���� ����

    _devices->ImmediateContext()->RSSetViewports(1, &screenViewport);
}

void D3D11Context_mk2::BeginRender(const float* color) const
{
    // �ĸ� ���۸� ������ ������ ����
    _devices->ImmediateContext()
        ->ClearRenderTargetView(_resourceView->renderTargetView.Get(), color);
    // ���̹��۸� 1.0f, ���ٽ� ���۸� 0 ���� ����
    _devices->ImmediateContext()
        ->ClearDepthStencilView(_resourceView->depthStencilView.Get(),
                                D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                1.0f,
                                0);
    _devices->ImmediateContext()
        ->OMSetDepthStencilState(_renderState->normalDSS.Get(),
                                 0); // ���ϸ� ���� ���� ������ �׷���)
}

void D3D11Context_mk2::EndRender() const
{
    // �ĸ� ���� ����
    _swapChain->Present(0, 0);
}

} // namespace graphics