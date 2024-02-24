/// 2024-01-15

#include "D3D11Context.h"

#include <cassert>

namespace graphics
{

D3D11Context::D3D11Context(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight)
    : _devices(std::make_unique<Devices>())
    , _renderState(std::make_unique<D3D11RenderStates>(_devices->Device()))
    , _states(std::make_unique<DirectX::CommonStates>(_devices->Device()))
{
    // XMMATRIX�� ��������� ����
    DirectX::XMMATRIX identityMatrix = DirectX::XMMatrixIdentity();

    // XMMATRIX�� XMFLOAT4X4�� ��ȯ�Ͽ� �ʱ�ȭ
    DirectX::XMStoreFloat4x4(&_worldMatrix, identityMatrix);
    DirectX::XMStoreFloat4x4(&_projectionMatrix, identityMatrix);
    DirectX::XMStoreFloat4x4(&_orthoMatrix, identityMatrix);

    CreateSwapChain(hWnd, clientWidth, clientHeight);
    // CreateDepthStencilState();

    OnResize(clientWidth, clientHeight);
}

D3D11Context::~D3D11Context()
{
}

void D3D11Context::Finalize()
{
    _swapChain->SetFullscreenState(false, nullptr);
}

ID3D11Device* D3D11Context::GetDevice() const
{
    return _devices->Device();
}

ID3D11DeviceContext* D3D11Context::GetDeviceContext() const
{
    return _devices->ImmediateContext();
}

const Devices* D3D11Context::GetDevices() const
{
    return _devices.get();
}

D3D11RenderStates* D3D11Context::GetRenderStates() const
{
    return _renderState.get();
}

void D3D11Context::SetBackBufferRenderTarget()
{
    GetDeviceContext()->OMSetRenderTargets(
        1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
}

void D3D11Context::ResetViewport()
{
    GetDeviceContext()->RSSetViewports(1, &_viewport);
}

void D3D11Context::CreateSwapChain(HWND hWnd, int width, int height)
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

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice{ nullptr };
    _devices->Device()->QueryInterface(
        __uuidof(IDXGIDevice), (void**)dxgiDevice.GetAddressOf());

    // �׷��� ī�� ��� ����
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter{ nullptr };
    dxgiDevice->GetParent(
        __uuidof(IDXGIAdapter), (void**)dxgiAdapter.GetAddressOf());

    // DirectX �׷��� �������̽� ���丮 ����
    Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory{ nullptr };
    dxgiAdapter->GetParent(
        __uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf());

    // ���� ü�� ����
    dxgiFactory->CreateSwapChain(
        _devices->Device(), &swapChain, _swapChain.GetAddressOf());

    assert(_swapChain.Get());
}

void D3D11Context::CreateDepthStencilState()
{
    // ���Ľ� ������Ʈ ����ü �ʱ�ȭ
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    // ���Ľ� ������Ʈ ����ü ����
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���̹��ۿ� ����� �Ѵ�
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    // ��Ʈ�� ���� ���ٽ� ������Ʈ ����
    _devices->Device()->CreateDepthStencilState(
        &depthStencilDesc, _normalDSS.GetAddressOf());
    assert(_normalDSS);

    depthStencilDesc.StencilEnable    = true;
    depthStencilDesc.StencilReadMask  = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // �ȼ� ���� ���ٽ� ����
    depthStencilDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

    // �ȼ� �޸� ���ٽ� ����
    depthStencilDesc.BackFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

    // ���� ���ٽ� ������Ʈ ����
    _devices->Device()->CreateDepthStencilState(
        &depthStencilDesc, _depthStencilState.GetAddressOf());
    assert(_depthStencilState);

    // ���� ���ٽ� ���� ����
    _devices->DeferredContext()->OMSetDepthStencilState(
        _depthStencilState.Get(), 1);
}

void D3D11Context::InitializeMatrix(int width, int height)
{
    float fieldOfView{ (float)DirectX::XM_PIDIV4 };
    float screenAspect{ (float)width / (float)height };

    DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
        fieldOfView, screenAspect, 0000.1f, 10000.f);
    SetProjectionMatrix(proj);
    
    DirectX::XMMATRIX ortho = DirectX::XMMatrixOrthographicLH(
        fieldOfView, screenAspect, 0000.1f, 10000.f);
    SetOrthoMatrix(ortho);
}

void D3D11Context::OnResize(int width, int height)
{
    // ���� ��� ���� ����/���ٽ� ���۸� ����
    _renderTargetView.Reset();

    // ���� ü�ΰ� ���� Ÿ�� �缳��
    _swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
     Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    /// ���� Ÿ�� �� ����

    // ��ȯ �罽 ������ ���
    _swapChain->GetBuffer(0,
        __uuidof(ID3D11Texture2D),
         reinterpret_cast<void**>(backBuffer.GetAddressOf()));


    // ���� Ÿ�� �� ����
    assert(backBuffer != 0);

    GetDevice()->CreateRenderTargetView(
        backBuffer.Get(), 0, _renderTargetView.GetAddressOf());

    assert(_renderTargetView.Get());

    /// ����/���ٽ� ���� ����

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = width;  // �ؽ�ó �ʺ�
    depthStencilDesc.Height    = height; // �ؽ�ó ����
    depthStencilDesc.MipLevels = 1;      // �ؽ�ó�� Minmap ���� ��
    depthStencilDesc.ArraySize = 1;      // �ؽ�ó �迭�� �ؽ�ó ��
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // ����

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    // �ؽ�ó�� �а� ���� ��� �ĺ�

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.CPUAccessFlags = 0; // CPU ���� ��� ���� �÷��� (������� �ʾ�, 0)
    // depthStencilDesc.Usage = D3D11_USAGE_DYNAMIC;
    // depthStencilDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // ������������ ���ε� �÷���
    depthStencilDesc.MiscFlags = 0; // ��Ÿ ���ҽ� �ɼ� �÷���

    ///  ���� ���ٽ� ���� ����

    GetDevice()->CreateTexture2D(&depthStencilDesc,
        0,
        _depthStencilBuffer.GetAddressOf()); // ����/���ٽ� ���� ��ȯ

    assert(_depthStencilBuffer);

    /// ���� ���ٽ� �� ����

    GetDevice()->CreateDepthStencilView(
        _depthStencilBuffer.Get(), 0, _depthStencilView.GetAddressOf());

    assert(_depthStencilView.Get());

    /// ����� ��� ���ձ� �ܰ迡 ����

    // ���� Ÿ�� ��� ���� ���ٽ� ���۸� ��� ���� ���������ο� ���ε�
    GetDeviceContext()->OMSetRenderTargets(
        1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());

    assert(_renderTargetView.Get());

    /// ����Ʈ ����
    _viewport.TopLeftX = 0;
    _viewport.TopLeftY = 0;
    _viewport.Width    = static_cast<float>(width);
    _viewport.Height   = static_cast<float>(height);
    _viewport.MinDepth = 0.0f; // �ּ� ���� ����
    _viewport.MaxDepth = 1.0f; // �ִ� ���� ����

    GetDeviceContext()->RSSetViewports(1, &_viewport);

    // ���� ���� ��� & ���� ���� ��� �ʱ�ȭ
    InitializeMatrix(width, height);
}

void D3D11Context::BeginRender(const float* color) const
{
    // �� ���۸� ������ ������ ����
    _devices->ImmediateContext()->ClearRenderTargetView(
        _renderTargetView.Get(), color);

    // ���� ���۸� 1.0f(�ִ밪), ���ٽ� ���۸� 0���� �ʱ�ȭ
    _devices->ImmediateContext()->ClearDepthStencilView(
        _depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // (���ϸ� ���� ���� ������ �׷���)
    _devices->ImmediateContext()->OMSetDepthStencilState(_depthStencilState.Get(), 0);
}

void D3D11Context::EndRender() const
{
    // �ĸ� ���� ����
    _swapChain->Present(0, 0);
}

DirectX::XMMATRIX D3D11Context::GetWorldMatrix()
{
    return DirectX::XMLoadFloat4x4(&_worldMatrix);
}

DirectX::XMMATRIX D3D11Context::GetProjectMatrix()
{
    return DirectX::XMLoadFloat4x4(&_projectionMatrix);
}

DirectX::XMMATRIX D3D11Context::GetOrthographicMatrix()
{
    return DirectX::XMLoadFloat4x4(&_orthoMatrix);
}

void D3D11Context::SetWorldMatrix(DirectX::XMMATRIX& world)
{
    DirectX::XMStoreFloat4x4(&_worldMatrix, world);
}

void D3D11Context::SetProjectionMatrix(DirectX::XMMATRIX& project)
{
    DirectX::XMStoreFloat4x4(&_projectionMatrix, project);
}

void D3D11Context::SetOrthoMatrix(DirectX::XMMATRIX& ortho)
{
    DirectX::XMStoreFloat4x4(&_orthoMatrix, ortho);
}

void D3D11Context::TurnZBufferOn()
{
    GetDeviceContext()->OMSetDepthStencilState(_depthStencilState.Get(), 1);
}

void D3D11Context::TurnZBufferOff()
{
    GetDeviceContext()->OMSetDepthStencilState(_depthStencilState.Get(), 1);
}

} // namespace graphics