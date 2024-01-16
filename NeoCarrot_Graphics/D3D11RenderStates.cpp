#include "D3D11RenderStates.h"
#include <d3d11.h>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

graphics::D3D11RenderStates::D3D11RenderStates(ID3D11Device* _d3dDevice)
{
	assert(_d3dDevice);

	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	_d3dDevice->CreateRasterizerState(&solidDesc, &_solidRS);

	assert(_solidRS);

	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	_d3dDevice->CreateRasterizerState(&wireframeDesc, &_wireframeRS);

	assert(_wireframeRS);


	// 폰트용 DSS
	D3D11_DEPTH_STENCIL_DESC equalsDesc;
	ZeroMemory(&equalsDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	equalsDesc.DepthEnable = true;
	equalsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;	// 깊이버퍼에 쓰기는 한다
	equalsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	_d3dDevice->CreateDepthStencilState(&equalsDesc, &_normalDSS);

	assert(_normalDSS);

#ifdef _DEBUG
    std::cout << "\tD3D11RenderStates Constructed\n";
#endif // _DEBUG
}

graphics::D3D11RenderStates::~D3D11RenderStates()
{
	if(_normalDSS) _normalDSS->Release();
	if(_wireframeRS) _wireframeRS->Release();
}

ID3D11RasterizerState* graphics::D3D11RenderStates::WireFrame()
{
	return _wireframeRS;
}

ID3D11RasterizerState* graphics::D3D11RenderStates::Solid()
{
	return _solidRS;
}
