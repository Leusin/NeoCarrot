///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "Matrix.h"

namespace game
{

class Transform : public core::IComponent
{
public:
    Transform();
    ~Transform();

    /*
    
    	DirectX::XMMATRIX GetWorld();
		DirectX::XMMATRIX GetView();
		DirectX::XMMATRIX GetProj();
		
		void SetWorld(const DirectX::XMMATRIX& w);
		void SetView(const DirectX::XMMATRIX& v);
		void SetProj(const DirectX::XMMATRIX& p);

		// world, view, proj �� �Ѳ����� �ʱ�ȭ
		void SetTM(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj);

		DirectX::XMMATRIX WorldViewProj();
		// world, view, proj ���� ��ȯ

    */

private:
    me::Matrix _world;
    me::Matrix _view;
    me::Matrix _proj;
};

} // namespace game