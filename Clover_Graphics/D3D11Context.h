/// D3D11Context_mk2.h
///
/// 2024-01-14

#pragma once

#include "D3D11Devices.h"
#include "D3D11RenderStates.h"
#include "DDSTexture.h"

#include <d3d11.h>
#include <directxmath.h>
#include <dxgi.h>
#include <memory>
#include <wrl.h>
//#include <CommonStates.h>
#include "./DirectXTK/Inc/CommonStates.h"

namespace graphics
{

// 본문
class D3D11Context
{
public:
    D3D11Context(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
    ~D3D11Context();

    void Finalize();

    ID3D11Device* GetDevice() const;
    ID3D11DeviceContext* GetDeviceContext() const;
    const Devices* GetDevices() const;
    D3D11RenderStates* GetRenderStates() const;

    void OnResize(int width, int height);
    void BeginRender(const float* color) const;
    void EndRender() const;

    DirectX::XMMATRIX GetWorldMatrix();
    DirectX::XMMATRIX GetProjectMatrix();
    DirectX::XMMATRIX GetOrthographicMatrix();

    void SetWorldMatrix(DirectX::XMMATRIX& world);
    void SetProjectionMatrix(DirectX::XMMATRIX& project);
    void SetOrthoMatrix(DirectX::XMMATRIX& ortho);

private:
    void CreateSwapChain(HWND hWnd, int width, int height);
    void CreateDepthStencilState();

    void InitializeMatrix(int width, int height);

    // 디비이스와 디바이스 컨텍스트를 캡슐화한 객체
    std::unique_ptr<Devices> _devices{ nullptr };

    /// <summary>
    /// 두 개 이상의 백버퍼를 관리하는 객체.
    /// </summary>
    Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain{ nullptr };
    
    // ----------------------------------------------------------------------

    /// <summary>
    /// 랜더링의 대상의 현재 속성들을 정의한 객체.
    /// 그래픽스 출력되는 것이 적혀 있음.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView{ nullptr };

    std::unique_ptr<D3D11RenderStates> _renderState{ nullptr };

    // ----------------------------------------------------------------------

    /// <summary>
    /// HSV(hidden surface removal)에 사용되는 z-버퍼를 가진 그래픽스 리소스.
    /// 2d에서는 사용되지 않고 3d에서 그려질 픽세들을 정렬하는데 사용한다.
    /// 스텐실 버퍼에 대한 설정도 할 수 있다.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _normalDSS{ nullptr }; // 폰트용

    // 나중에써야징
    std::unique_ptr<DirectX::CommonStates> _states;

    /// <summary>
    /// 현재 뎁스/스텐실 리소스 속성을 정의한 인터페이스 객체.
    /// </summary>
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView{ nullptr };

    // ----------------------------------------------------------------------

   DirectX::XMFLOAT4X4 _worldMatrix;
   DirectX::XMFLOAT4X4 _projectionMatrix;
   DirectX::XMFLOAT4X4 _orthoMatrix;

};

} // namespace graphics

//
// 리소스 뷰의 종류.
//
// - ID3D11DepthStencilView : 뎁스 스텐실 테스팅 할 때 텍스처 리소스 접근
// - ID3D11RenderTargetView : 랜더 타깃의 텍스처 에 접근
// - ID3D11ShaderResourceView : 상수 버퍼, 텍스처 버퍼, 텍스처나 샘플러 같은 셰이터에 접근
// - ID3D11UnorderedAccessView : 픽셀 셰이더나 컴퓨트 셰이더를 사용하여 정렬되지 않은 리소스에 접근
//
// 2024-01-15