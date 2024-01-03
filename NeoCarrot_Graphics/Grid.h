#pragma once

#include "Transpose.h"
#include <wrl.h>
#include <directXMath.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D11RasterizerState;
struct ID3D11InputLayout;
struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;

namespace ge
{
	class Grid
	{
	public:
		Grid(ID3D11Device* d, ID3D11DeviceContext* dc, ID3D11RasterizerState* rs);
		virtual ~Grid();

		struct Vertex
		{
			DirectX::XMFLOAT3 Pos;
			DirectX::XMFLOAT4 Color;
		};

		virtual void Render();

		void SetEyePosW(DirectX::XMFLOAT3 val) { _eyePosW = val; }

		// 변환
		Transpose _transpose;

	protected:
		
		void BuildGeometryBuffers();
		void BuildFX();
		void BuildVertexLayout();

		// 디바이스
		ID3D11Device* _d3dDevice{ nullptr };

		// 디바이스 컨텍스트
		ID3D11DeviceContext* _d3dImmediateContext{ nullptr };

		// 버텍스버퍼
		Microsoft::WRL::ComPtr<ID3D11Buffer> _vb{ nullptr };

		// 인덱스버퍼
		Microsoft::WRL::ComPtr<ID3D11Buffer> _ib{ nullptr };

		// RasterizerState 어떻게 랜더할 것인가
		ID3D11RasterizerState* _renderstate;

		// 입력 레이아웃
		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout{ nullptr };

		// 카메라 위치
		DirectX::XMFLOAT3 _eyePosW;

		// 이펙트
		Microsoft::WRL::ComPtr<ID3DX11Effect> _fx{ nullptr };
		Microsoft::WRL::ComPtr<ID3DX11EffectTechnique> _tech{ nullptr };
		Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _fxWorldViewProj{ nullptr };
	};
}