#pragma once

#include <directxmath.h>

namespace graphics
{

struct MatrixBufferType
{
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};

struct LightBufferType
{
    DirectX::XMFLOAT4 diffuseColor;
    DirectX::XMFLOAT3 lightDirection;
    float padding; // ����ü�� 16����� �ǵ��� ������ �е��� �߰��Ѵٴµ�...?
};

}