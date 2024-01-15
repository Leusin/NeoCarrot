#include "RenderStates.h"
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

RenderStates::RenderStates(ID3D11Device* _d3dDevice)
{
    CreateWireFrameRanderState(_d3dDevice);
    CreateSolidRenderState(_d3dDevice);

    CreateNormalDepthStencilState(_d3dDevice);

#ifdef _DEBUG
    std::cout << "\t\tRenderStates Constructed\n";
#endif // _DEBUG
}

RenderStates::~RenderStates()
{
    //if (_normalDSS) _normalDSS->Release();
    //if (_solidRS) _solidRS->Release();
    //if (_wireframeRS) _wireframeRS->Release();
}

void RenderStates::CreateWireFrameRanderState(ID3D11Device* _d3dDevice)
{
    assert(_d3dDevice);

    D3D11_RASTERIZER_DESC solidDesc;
    ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
    solidDesc.FillMode              = D3D11_FILL_SOLID;
    solidDesc.CullMode              = D3D11_CULL_BACK;
    solidDesc.FrontCounterClockwise = false;
    solidDesc.DepthClipEnable       = true;

    _d3dDevice->CreateRasterizerState(&solidDesc, _solidRS.GetAddressOf());

    assert(_solidRS);
}

void RenderStates::CreateSolidRenderState(ID3D11Device* _d3dDevice)
{
    assert(_d3dDevice);

    D3D11_RASTERIZER_DESC wireframeDesc;
    ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
    wireframeDesc.FillMode              = D3D11_FILL_WIREFRAME;
    wireframeDesc.CullMode              = D3D11_CULL_BACK;
    wireframeDesc.FrontCounterClockwise = false;
    wireframeDesc.DepthClipEnable       = true;

    _d3dDevice->CreateRasterizerState(&wireframeDesc, _wireframeRS.GetAddressOf());

    assert(_wireframeRS);
}

void RenderStates::CreateNormalDepthStencilState(ID3D11Device* _d3dDevice)
{
    assert(_d3dDevice);

    D3D11_DEPTH_STENCIL_DESC equalsDesc;
    ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    equalsDesc.DepthEnable    = true;
    equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이버퍼에 쓰기는 한다
    equalsDesc.DepthFunc      = D3D11_COMPARISON_LESS;

    _d3dDevice->CreateDepthStencilState(&equalsDesc, _normalDSS.GetAddressOf());

    assert(_normalDSS);
}

} // namespace graphics