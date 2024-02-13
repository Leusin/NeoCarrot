/// RenderState.h : 여러 RenderState 객체를 관리하는 클래스
/// 
/// 2021-12-27
///

#pragma once

#include <d3d11.h>
#include <wrl.h>

namespace graphics
{
class D3D11RenderStates
{
public:
	D3D11RenderStates(ID3D11Device* divice);
	~D3D11RenderStates();

	ID3D11RasterizerState* WireFrame();
    ID3D11RasterizerState* Solid();

private:
    Microsoft::WRL::ComPtr <ID3D11RasterizerState> _wireframeRS{ nullptr };
    Microsoft::WRL::ComPtr <ID3D11RasterizerState> _solidRS{ nullptr };

};

} // GraphicsEngine
