/// ��ǲ ���̾ƿ�
/// 
/// 2024-01-24


#pragma once

#include <d3dx11effect.h>
#include <directxmath.h>
#include <vector>

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