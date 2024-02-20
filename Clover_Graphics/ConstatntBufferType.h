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
    float padding; // 구조체가 16배수가 되도록 여분의 패딩을 추가한다는데...?
};

}

/*
struct ConstBuffWorldViewProj
{
    DirectX::XMMATRIX WorldViewProj;
};

struct ConstBuffLit
{
    DirectX::XMMATRIX mWorld;
    DirectX::XMMATRIX mView;
    DirectX::XMMATRIX mProjection;
    DirectX::XMFLOAT4 vLightDir[2];
    DirectX::XMFLOAT4 vLightColor[2];
    DirectX::XMFLOAT4 vOutputColor;
};
*/