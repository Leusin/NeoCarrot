#pragma once

#include <directxmath.h>

#include "IComponent.h"

namespace graphics
{
	class Transpose : public core::IComponent
	{
	public:
		Transpose();
		~Transpose();

		void Awake() override;
		void Update(float dt) override;

		DirectX::XMMATRIX GetWorld();
		DirectX::XMMATRIX GetView();
		DirectX::XMMATRIX GetProj();
		DirectX::XMMATRIX GetObj();
		
		void SetWorld(const DirectX::XMMATRIX& w);
		void SetView(const DirectX::XMMATRIX& v);
		void SetProj(const DirectX::XMMATRIX& p);
		void SetObj(const DirectX::XMMATRIX& o);

		// world, view, proj �� �Ѳ����� �ʱ�ȭ
		void SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj);

		DirectX::XMMATRIX WorldViewProj();
		// world, view, proj ���� ��ȯ

	private:
        // ��ȯ ���� 
		DirectX::XMFLOAT4X4 _world; // ���� ��ȯ ��� (����->����)
		DirectX::XMFLOAT4X4 _view; // �þ� ��ȯ ��� (ī�޶� ��)
		DirectX::XMFLOAT4X4 _proj; // ���� ��ȯ ��� (����/����)

		// ī�޶� ��ġ
        DirectX::XMFLOAT3 _eyePosW; 

		// ���� ��ǥ
        DirectX::XMFLOAT4X4 _objWorld;
	}; 
}