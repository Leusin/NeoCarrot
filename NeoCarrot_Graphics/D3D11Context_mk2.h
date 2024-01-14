/// D3D11Context_mk2.h
///
/// 2024-01-14

#pragma once

#include <dxgi.h>
#include <memory>
#include <wrl.h>

namespace graphics
{
// 전방 선언
class Devices;
struct ResourceView;

// 본문
class D3D11Context_mk2
{
public:
    D3D11Context_mk2(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
    ~D3D11Context_mk2();

    Devices*      GetDevices();
    void          CreateSwapChain(HWND hWnd, int width, int height);
    ResourceView* GetResourceView();

    void OnResize(int width, int height);
    void BeginRender(const float* color) const;
    void EndRender() const;

private:
    std::unique_ptr<Devices>               _devices;
    Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
    std::unique_ptr<ResourceView>          _resourceView;
};

} // namespace graphics