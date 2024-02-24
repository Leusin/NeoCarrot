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

// ����
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

    void TurnZBufferOn();
    void TurnZBufferOff();
    //void TurnOnAlphaBlending();
    //void TurnOffAlphaBlending();
    //void TurnOnCulling();
    //void TurnOffCulling();

    void SetBackBufferRenderTarget();
    void ResetViewport();

private:
    void CreateSwapChain(HWND hWnd, int width, int height);
    void CreateDepthStencilState();

    void InitializeMatrix(int width, int height);


    // �� �� �̻��� ����۸� �����ϴ� ��ü.
    Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain{ nullptr };
    
    // ����̽��� ����̽� ���ؽ�Ʈ�� ĸ��ȭ�� ��ü
    std::unique_ptr<Devices> _devices{ nullptr };

    // �������� ����� ���� �Ӽ����� ������ ��ü.
    // �׷��Ƚ� ��µǴ� ���� ���� ����.
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView{ nullptr };

    // HSV(hidden surface removal)�� ���Ǵ� z-���۸� ���� �׷��Ƚ� ���ҽ�.
    // 2d������ ������ �ʰ� 3d���� �׷��� �ȼ����� �����ϴµ� ����Ѵ�.
    // ���ٽ� ���ۿ� ���� ������ �� �� �ִ�.
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _normalDSS{ nullptr }; // ��Ʈ��

    // ���� ����/���ٽ� ���ҽ� �Ӽ��� ������ �������̽� ��ü.
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView{ nullptr };

    std::unique_ptr<D3D11RenderStates> _renderState{ nullptr };

    // ���߿����¡
    std::unique_ptr<DirectX::CommonStates> _states;

    // ----------------------------------------------------------------------

   DirectX::XMFLOAT4X4 _worldMatrix;
   DirectX::XMFLOAT4X4 _projectionMatrix;
   DirectX::XMFLOAT4X4 _orthoMatrix;

   D3D11_VIEWPORT _viewport;

};

} // namespace graphics

//
// ���ҽ� ���� ����.
//
// - ID3D11DepthStencilView : ���� ���ٽ� �׽��� �� �� �ؽ�ó ���ҽ� ����
// - ID3D11RenderTargetView : ���� Ÿ���� �ؽ�ó �� ����
// - ID3D11ShaderResourceView : ��� ����, �ؽ�ó ����, �ؽ�ó�� ���÷� ���� �����Ϳ� ����
// - ID3D11UnorderedAccessView : �ȼ� ���̴��� ��ǻƮ ���̴��� ����Ͽ� ���ĵ��� ���� ���ҽ��� ����
//
// 2024-01-15