/// 버텍스 버퍼 구조체
///
/// 2024-01-24

#pragma once

#include <directxmath.h>
#include <vector>

namespace graphics
{
struct Pos
{
    DirectX::XMFLOAT3 Position;
};

struct Col
{
    DirectX::XMFLOAT4 Color;
};

struct PosCol: public Pos, public Col
{
};

struct Nol
{
    DirectX::XMFLOAT3 Normal;
};

struct Tex
{
    DirectX::XMFLOAT2 Texture;
};

struct Weights
{
    DirectX::XMFLOAT3 Weights;
};

struct Boneidx
{
    int BoneIndices;
};

} // namespace graphics