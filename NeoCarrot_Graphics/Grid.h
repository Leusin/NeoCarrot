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

		// ��ȯ
		Transpose _transpose;

	protected:
		
		void BuildGeometryBuffers();
		void BuildFX();
		void BuildVertexLayout();

		// ����̽�
		ID3D11Device* _d3dDevice{ nullptr };

		// ����̽� ���ؽ�Ʈ
		ID3D11DeviceContext* _d3dImmediateContext{ nullptr };

		// ���ؽ�����
		Microsoft::WRL::ComPtr<ID3D11Buffer> _vb{ nullptr };

		// �ε�������
		Microsoft::WRL::ComPtr<ID3D11Buffer> _ib{ nullptr };

		// RasterizerState ��� ������ ���ΰ�
		ID3D11RasterizerState* _renderstate;

		// �Է� ���̾ƿ�
		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout{ nullptr };

		// ī�޶� ��ġ
		DirectX::XMFLOAT3 _eyePosW;

		// ����Ʈ
		Microsoft::WRL::ComPtr<ID3DX11Effect> _fx{ nullptr };
		Microsoft::WRL::ComPtr<ID3DX11EffectTechnique> _tech{ nullptr };
		Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _fxWorldViewProj{ nullptr };
	};
}