#pragma once

#include <directxmath.h>
#include <d3dx11effect.h>
#include <vector>

namespace graphics
{

//
// 구조체 버퍼
//
struct Pos
{
    DirectX::XMFLOAT3 Pos;
};

struct PosCol
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

struct PosNormal
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
};

struct PosNormalTex
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
};

struct PosNormalTexWeightsBoneidx
{
    DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
    DirectX::XMFLOAT3 Weights;
    int               BoneIndices;
};

//
// 인풋 레이아웃
//

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosColorDesc =
{
     {"POSITION",
     0, 
     DXGI_FORMAT_R32G32B32_FLOAT, 
     0,
     0, D3D11_INPUT_PER_VERTEX_DATA, 
     0},
     {"COLOR", 
     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 
     0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalDesc =
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalTex = {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalTexWeightsBoneidxDesc =
{
     {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
     {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
     {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
     {"WEIGHTS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
     {"BONEINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

} // namespace graphics