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
    void Update(float dt) override;

    void SetFromMesh(const model::Mesh& data);
    void SetBuffers(unsigned int& offset);

    // ���ؽ�����
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vb;
    std::vector<V>   _vertices;
    std::vector<int> _vertexOffset;
    unsigned int                         _totalVertexCount;

private:
    
    void SetBuffers(unsigned int& stride, unsigned int& offset);

    D3Devices*     _d3device;
};

template <typename V>
inline VertexBuffer<V>::VertexBuffer(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr)),
    _d3device{GetComponent<graphics::D3Devices>()}
{
    static_assert(std::is_class<V>::value, "VertexBuffer �� �޴� V �� ����ü(Ŭ����)�� ��");
    assert(_d3device && "VertexBuffer ���� D3Devices �� ã�� �� ����");

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
inline void VertexBuffer<V>::Update(float dt)
{
    //SetBuffers();
}

template <typename V>
inline void VertexBuffer<V>::SetFromMesh(const model::Mesh& data)
{
    // �а� �ִ� �޽��� ���� ũ��
    UINT vcount = static_cast<UINT>(data.vertices.size());

    // �а� �ִ� �Žð� ���۵� ���� ����
    _vertexOffset.emplace_back(_totalVertexCount);

    // ��ü ���� ��
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
        /// �̿ϼ� 
        ///    ���� �����غ�����.
        /// 

        if (data.hasColor && !data.hasTexture && !data.hasNormal)
        {
            // PosCol
            _vertices.emplace_back(V{pos, col});
        }
        else if (!data.hasColor && data.hasTexture && !data.hasNormal)
        {
            // PosNormal
            _vertices.emplace_back(V{pos, nol});
        }
        else if (!data.hasColor && data.hasTexture && !data.hasNormal)
        {
            // PosNormalTex
            _vertices.emplace_back(V{pos, nol, uv});
        }
    }
}

template <typename V>
inline void VertexBuffer<V>::SetBuffers(unsigned int& stride, unsigned int& offset)
{
    // ���� ���� ��ġ ����
    _d3device->GetDeviceContext()->IASetVertexBuffers(0, 1, _vb.GetAddressOf(), &stride, &offset);
}

template <typename V>
inline void VertexBuffer<V>::SetBuffers(unsigned int& offset)
{
    unsigned int stride = static_cast<unsigned int>(sizeof(V));
    SetBuffers(stride, offset);
}

} // namespace graphics