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
    // XMMATRIX의 단위행렬을 생성
    DirectX::XMMATRIX identityMatrix = DirectX::XMMatrixIdentity();

    // XMMATRIX를 XMFLOAT4X4로 변환하여 초기화
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

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice{ nullptr };
    _devices->Device()->QueryInterface(
        __uuidof(IDXGIDevice), (void**)dxgiDevice.GetAddressOf());

    // 그래픽 카드 어뎁터 생성
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter{ nullptr };
    dxgiDevice->GetParent(
        __uuidof(IDXGIAdapter), (void**)dxgiAdapter.GetAddressOf());

    // DirectX 그래픽 인터페이스 펙토리 생성
    Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory{ nullptr };
    dxgiAdapter->GetParent(
        __uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf());

    // 스왑 체인 생성
    dxgiFactory->CreateSwapChain(
        _devices->Device(), &swapChain, _swapChain.GetAddressOf());

    assert(_swapChain.Get());
}

void D3D11Context::CreateDepthStencilState()
{
    // 스탠실 스테이트 구조체 초기화
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    // 스탠실 스테이트 구조체 설정
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이버퍼에 쓰기는 한다
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    // 폰트용 뎁스 스텐실 스테이트 생성
    _devices->Device()->CreateDepthStencilState(
        &depthStencilDesc, _normalDSS.GetAddressOf());
    assert(_normalDSS);

    depthStencilDesc.StencilEnable    = true;
    depthStencilDesc.StencilReadMask  = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    // 픽셀 정면 스텐실 설정
    depthStencilDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

    // 픽셀 뒷면 스텐실 설정
    depthStencilDesc.BackFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

    // 뎁스 스텐실 스테이트 생성
    _devices->Device()->CreateDepthStencilState(
        &depthStencilDesc, _depthStencilState.GetAddressOf());
    assert(_depthStencilState);

    // 뎁스 스텐실 상태 설정
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
    // 이전 뷰와 이전 깊이/스텐실 버퍼를 해제
    _renderTargetView.Reset();

    // 스왑 체인과 랜더 타겟 재설정
    _swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
     Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    /// 랜더 타깃 뷰 생성

    // 교환 사슬 포인터 얻기
    _swapChain->GetBuffer(0,
        __uuidof(ID3D11Texture2D),
         reinterpret_cast<void**>(backBuffer.GetAddressOf()));


    // 랜더 타겟 뷰 생성
    assert(backBuffer != 0);

    GetDevice()->CreateRenderTargetView(
        backBuffer.Get(), 0, _renderTargetView.GetAddressOf());

    assert(_renderTargetView.Get());

    /// 깊이/스텐실 버퍼 생성

    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = width;  // 텍스처 너비
    depthStencilDesc.Height    = height; // 텍스처 높이
    depthStencilDesc.MipLevels = 1;      // 텍스처의 Minmap 수준 수
    depthStencilDesc.ArraySize = 1;      // 텍스처 배열의 텍스처 수
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT; // 형식

    depthStencilDesc.SampleDesc.Count   = 1;
    depthStencilDesc.SampleDesc.Quality = 0;

    // 텍스처를 읽고 쓰는 방법 식별

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.CPUAccessFlags = 0; // CPU 접근 허용 유형 플래그 (사용하지 않아, 0)
    // depthStencilDesc.Usage = D3D11_USAGE_DYNAMIC;
    // depthStencilDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 파이프라인의 바인딩 플래그
    depthStencilDesc.MiscFlags = 0; // 기타 리소스 옵션 플래그

    ///  뎁스 스텐실 버퍼 생성

    GetDevice()->CreateTexture2D(&depthStencilDesc,
        0,
        _depthStencilBuffer.GetAddressOf()); // 깊이/스텐실 버퍼 반환

    assert(_depthStencilBuffer);

    /// 뎁스 스텐실 뷰 생성

    GetDevice()->CreateDepthStencilView(
        _depthStencilBuffer.Get(), 0, _depthStencilView.GetAddressOf());

    assert(_depthStencilView.Get());

    /// 뷰들을 출력 병합기 단계에 묶기

    // 랜더 타깃 뷰와 뎁스 스텐실 버퍼를 출력 렌더 파이프라인에 바인딩
    GetDeviceContext()->OMSetRenderTargets(
        1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());

    assert(_renderTargetView.Get());

    /// 뷰포트 설정
    _viewport.TopLeftX = 0;
    _viewport.TopLeftY = 0;
    _viewport.Width    = static_cast<float>(width);
    _viewport.Height   = static_cast<float>(height);
    _viewport.MinDepth = 0.0f; // 최소 깊이 버퍼
    _viewport.MaxDepth = 1.0f; // 최대 깊이 버퍼

    GetDeviceContext()->RSSetViewports(1, &_viewport);

    // 원근 투영 행렬 & 직교 투영 행렬 초기화
    InitializeMatrix(width, height);
}

void D3D11Context::BeginRender(const float* color) const
{
    // 백 버퍼를 지정돤 색으로 지움
    _devices->ImmediateContext()->ClearRenderTargetView(
        _renderTargetView.Get(), color);

    // 뎁스 버퍼를 1.0f(최대값), 스텐실 버퍼를 0으로 초기화
    _devices->ImmediateContext()->ClearDepthStencilView(
        _depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    // (안하면 뒤의 것이 앞으로 그려짐)
    _devices->ImmediateContext()->OMSetDepthStencilState(_depthStencilState.Get(), 0);
}

void D3D11Context::EndRender() const
{
    // 후면 버퍼 제시
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