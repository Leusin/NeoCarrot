#pragma once

#include <d3dx11effect.h>
#include <directxmath.h>
#include <vector>

namespace graphics
{

//
// ����ü ����
//

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


struct Pos
{
    DirectX::XMFLOAT3 Pos;
};

struct Col: public Pos
{
    //DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT4 Color;
};

struct Nol: public Pos
{
    //DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
};

struct PosTex: public Pos
{
    // DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT2 Tex;
};

struct PosNormalTex: public Pos
{
    //DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
};

struct PosNormalTexWeightsBoneidx: public Pos
{
    //DirectX::XMFLOAT3 Pos;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 Tex;
    DirectX::XMFLOAT3 Weights;
    int BoneIndices;
};

//
// ��ǲ ���̾ƿ�
//

static const std::vector<D3D11_INPUT_ELEMENT_DESC> posDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//
// �ø�ƽ ���� / �ø�ƽ �ε��� / ���� / ��ǲ���� / ������ / ��ǲ ���� Ŭ���� /
// �ν��Ͻ� ������ ���� ����Ʈ
//
// �ø�ƽ ����
//    ��ҹ��ڸ� �������� �ʽ��ϴ�.
//
// �ø�ƽ ���� �ε���
//     "COLOR0" �� "COLOR1"�� ���� ���ڰ� �߰��� �ø�ƽ �̸��� ����ϴ� ���,
//     �� ��Ҵ� ���� �ٸ� �ø�ƽ �ε��� 0�� 1�� ����Ͽ� ���� �ø�ƽ �̸���
//     "COLOR"�� ������ �� �ֽ��ϴ�.
//
// ������ �ڼ��� ������
//    https://learn.microsoft.com/en-us/previous-versions//ff729719(v=vs.85)?redirectedfrom=MSDN
//

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosColorDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalTexDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static const std::vector<D3D11_INPUT_ELEMENT_DESC> PosNormalTexWeightsBoneidxDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "WEIGHTS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "BONEINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

} // namespace graphics