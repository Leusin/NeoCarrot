/// 2024-01-15

#pragma once

#include <wrl.h>
#include <d3d11.h>

namespace graphics
{

struct ResourceView
{
    ResourceView();

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
};

} // namespace graphics