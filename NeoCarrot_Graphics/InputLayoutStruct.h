/// 인풋 레이아웃
/// 
/// 2024-01-24


#pragma once

#include <d3dx11effect.h>
#include <directxmath.h>
#include <vector>

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

namespace graphics
{
static const std::vector<D3D11_INPUT_ELEMENT_DESC> posDesc = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

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