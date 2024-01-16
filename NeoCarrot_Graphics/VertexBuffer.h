#pragma once

#include "IComponent.h"
#include "GetEntity.h"
#include "D3Devices.h"
#include "FbxLoader.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>
#include <cassert>
#include <directxmath.h>
#include <type_traits>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
template <typename V>
class VertexBuffer : public core::IComponent, virtual core::GetEntity
{
public:
    VertexBuffer(EntityPtr entityPtr);

    void Awake() override;

    void SetFromMesh(const model::Mesh& data);

    // 버텍스버퍼
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vb;
    std::vector<V>   _vertices;
    std::vector<int> _vertexOffset;
    UINT _totalVertexCount;

private:
    D3Devices*     _d3device;
};

template <typename V>
inline VertexBuffer<V>::VertexBuffer(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr)),
    _d3device{GetComponent<graphics::D3Devices>()}
{
    static_assert(std::is_class<V>::value, "VertexBuffer 가 받는 V 는 구조체(클래스)야 함");
    assert(_d3device && "VertexBuffer 에서 D3Devices 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexBuffer Component\n";
#endif // _DEBUG
}

template <typename V>
inline void VertexBuffer<V>::Awake()
{
    if (_vertices.empty()) return;

    D3D11_BUFFER_DESC vbd;
    vbd.Usage          = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth      = sizeof(V) * _totalVertexCount;
    vbd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags      = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = _vertices.data();
    _d3device->GetDevice()->CreateBuffer(&vbd, &vinitData, _vb.GetAddressOf());

}

template <typename V>
inline void VertexBuffer<V>::SetFromMesh(const model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    UINT vcount = static_cast<UINT>(data.vertices.size());

    // 읽고 있는 매시가 시작될 정점 숫자
    _vertexOffset.emplace_back(_totalVertexCount);

    // 전체 정점 수
    _totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        DirectX::XMFLOAT3 pos{data.vertices[i].position.x, data.vertices[i].position.y, data.vertices[i].position.z};

        DirectX::XMFLOAT4 col;
        if (data.hasColor)
        {
            col = {data.vertices[i].color.x, data.vertices[i].color.y, data.vertices[i].color.z, data.vertices[i].color.w};
        }

        DirectX::XMFLOAT2 uv;
        if (data.hasTexture)
        {
            uv = {data[i].uv.x, data[i].uv.y};
        }

        DirectX::XMFLOAT3 nol;
        if (data.hasNormal)
        {
            nol = {data.vertices[i].normal.x, data.vertices[i].normal.y, data.vertices[i].normal.z};
        }

        DirectX::XMFLOAT3 tan;
        DirectX::XMFLOAT3 bi;
        if (data.hasTangent)
        {
            tan = {data.vertices[i].tangent.x, data.vertices[i].tangent.y, data.vertices[i].tangent.z};
            bi  = {data.vertices[i].binormal.x, data.vertices[i].binormal.y, data.vertices[i].binormal.z};
        }

        ///
        /// 미완성 
        ///    좀더 생각해봐야함.
        /// 

        //_vertexBuffer->_vertices.emplace_back(V{pos, col, uv, nol, tan, bi});
    }
}

} // namespace graphics