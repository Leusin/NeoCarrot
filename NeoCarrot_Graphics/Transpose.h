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

		// world, view, proj 를 한꺼번에 초기화
		void SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj);

		DirectX::XMMATRIX WorldViewProj();
		// world, view, proj 곱을 반환

	private:
        // 변환 관련 
		DirectX::XMFLOAT4X4 _world; // 월드 변환 행렬 (로컬->월드)
		DirectX::XMFLOAT4X4 _view; // 시야 변환 행렬 (카메라 뷰)
		DirectX::XMFLOAT4X4 _proj; // 투영 변환 행렬 (원근/직교)

		// 카메라 위치
        DirectX::XMFLOAT3 _eyePosW; 

		// 월드 좌표
        DirectX::XMFLOAT4X4 _objWorld;
	}; 
}