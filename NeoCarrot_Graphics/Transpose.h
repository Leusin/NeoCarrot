#pragma once

#include <directXMath.h>


namespace grahics
{
	class Transpose
	{
	public:
		Transpose();
		~Transpose();

		DirectX::XMMATRIX GetWorld();
		DirectX::XMMATRIX GetView();
		DirectX::XMMATRIX GetProj();
		
		void SetWorld(const DirectX::XMMATRIX& w);
		void SetView(const DirectX::XMMATRIX& v);
		void SetProj(const DirectX::XMMATRIX& p);

		// world, view, proj 를 한꺼번에 초기화
		void SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj);

		DirectX::XMMATRIX WorldViewProj();
		// world, view, proj 곱을 반환

	private:
		DirectX::XMFLOAT4X4 _world;
		DirectX::XMFLOAT4X4 _view;
		DirectX::XMFLOAT4X4 _proj;
	}; 
}