#include "D3D11RenderStates.h"

#include <cassert>

graphics::D3D11RenderStates::D3D11RenderStates(ID3D11Device* _d3dDevice)
{
    assert(_d3dDevice);

    D3D11_RASTERIZER_DESC solidDesc;
    ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
    solidDesc.FillMode              = D3D11_FILL_SOLID;
    solidDesc.CullMode              = D3D11_CULL_BACK;
    solidDesc.FrontCounterClockwise = false;
    solidDesc.DepthClipEnable       = true;

    _d3dDevice->CreateRasterizerState(&solidDesc, &_solidRS);

    assert(_solidRS);

    D3D11_RASTERIZER_DESC wireframeDesc;
    ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
    wireframeDesc.FillMode              = D3D11_FILL_WIREFRAME;
    wireframeDesc.CullMode              = D3D11_CULL_BACK;
    wireframeDesc.FrontCounterClockwise = false;
    wireframeDesc.DepthClipEnable       = true;

    _d3dDevice->CreateRasterizerState(&wireframeDesc, &_wireframeRS);

    assert(_wireframeRS);
}

graphics::D3D11RenderStates::~D3D11RenderStates()
{
}

ID3D11RasterizerState* graphics::D3D11RenderStates::WireFrame()
{
    return _wireframeRS.Get();
}

ID3D11RasterizerState* graphics::D3D11RenderStates::Solid()
{
    return _solidRS.Get();
}
