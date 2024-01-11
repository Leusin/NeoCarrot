#pragma once

#include <directxmath.h>

namespace graphics
{
struct Pos
{
    DirectX::XMFLOAT3 Pos;
};

struct PosNormal
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
};

struct PosNolTex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
};

}