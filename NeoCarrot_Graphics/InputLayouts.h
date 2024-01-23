#pragma once

#include <d3dx11effect.h>
#include <directxmath.h>
#include <vector>

namespace graphics
{

//
// 구조체 버퍼
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
// 인풋 레이아웃
//

static const std::vector<D3D11_INPUT_ELEMENT_DESC> posDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//
// 시멘틱 네임 / 시멘틱 인덱스 / 포멧 / 인풋슬롯 / 오프셋 / 인풋 슬롯 클래스 /
// 인스턴스 데이터 스탭 레이트
//
// 시멘틱 네임
//    대소문자를 구분하지 않습니다.
//
// 시멘틱 네임 인덱스
//     "COLOR0" 및 "COLOR1"과 같이 숫자가 추가된 시맨틱 이름을 사용하는 대신,
//     두 요소는 서로 다른 시맨틱 인덱스 0과 1을 사용하여 단일 시맨틱 이름인
//     "COLOR"를 공유할 수 있습니다.
//
// 나머지 자세한 설명은
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