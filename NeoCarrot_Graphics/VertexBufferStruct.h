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
    DirectX::XMFLOAT3 Pos;
};

struct Col: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

struct Nol: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
};

struct PosTex: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT2 Tex;
};

struct PosNormalTex: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
};

struct PosNormalTexWeightsBoneidx: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
    DirectX::XMFLOAT3 Weights;
    int BoneIndices;
};

}