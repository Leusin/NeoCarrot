/// 구조체 버퍼
///
/// 2024-01-24


#pragma once

#include <directxmath.h>

namespace graphics
{

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

} // namespace graphics