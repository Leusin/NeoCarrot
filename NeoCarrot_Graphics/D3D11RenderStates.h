/// RenderState.h : 여러 RenderState 객체를 관리하는 클래스
/// 
/// 2021-12-27
///

#pragma once

struct ID3D11Device;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;

namespace graphics
{
class RenderStates
{
public:
	RenderStates(ID3D11Device* divice);
	~RenderStates();

	ID3D11RasterizerState* WireFrame();
	ID3D11RasterizerState* Solid();


	//폰트용. 
	// TODO - 다른 클래스로 분리할 것
	ID3D11DepthStencilState* _normalDSS{ nullptr };
private:
	ID3D11RasterizerState* _wireframeRS{ nullptr };
	ID3D11RasterizerState* _solidRS{ nullptr };

};

} // GraphicsEngine
