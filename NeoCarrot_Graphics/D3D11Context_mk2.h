/// D3D11Context_mk2.h
///
/// 2024-01-14

#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <memory>
#include <wrl.h>

namespace graphics
{
// ���� ����
class Devices;
struct ResourceView;
struct RenderStates;

// ����
class D3D11Context_mk2
{
public:
    D3D11Context_mk2(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
    ~D3D11Context_mk2();

    ID3D11Device* GetDevice() const;
    const Devices* GetDevices() const;
    ResourceView* GetResourceView() const;
    RenderStates* GetRenderStates() const;
    void          CreateSwapChain(HWND hWnd, int width, int height);

    void OnResize(int width, int height);
    void BeginRender(const float* color) const;
    void EndRender() const;

private:
    std::unique_ptr<Devices>               _devices;
    Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
    std::unique_ptr<ResourceView>          _resourceView;
    std::unique_ptr<RenderStates>          _renderState;
};

} // namespace graphics