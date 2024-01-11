/// RenderState.h : ���� RenderState ��ü�� �����ϴ� Ŭ����
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


	//��Ʈ��. 
	// TODO - �ٸ� Ŭ������ �и��� ��
	ID3D11DepthStencilState* _normalDSS{ nullptr };
private:
	ID3D11RasterizerState* _wireframeRS{ nullptr };
	ID3D11RasterizerState* _solidRS{ nullptr };

};

} // GraphicsEngine
