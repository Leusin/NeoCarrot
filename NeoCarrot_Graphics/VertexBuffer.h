#pragma once

#include "D3Device.h"
#include "Entity.h"
#include "EntityEnum.h"
#include "IComponent.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
template <typename V>
class VertexBuffer : public core::IComponent
{
public:
    VertexBuffer(EntityPtr entityPtr);

    void BuildBuffers();


private:
    EntityWeakPtr _entity;
    D3Device*     _d3device;

    // 버텍스버퍼
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vb;

    std::vector<V>   _vertices;
    std::vector<int> _vertexOffset;

    UINT _totalVertexCount;
};

template <typename V>
inline VertexBuffer<V>::VertexBuffer(EntityPtr entityPtr) :
_entity{EntityPtr(entityPtr)},
_d3device{_entity.lock()->GetComponent<graphics::D3Device>()}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexBuffer Component\n";
#endif // _DEBUG
}

template <typename V>
inline void VertexBuffer<V>::BuildBuffers()
{
    D3D11_BUFFER_DESC vbd;
    vbd.Usage          = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth      = sizeof(V) * _totalVertexCount;
    vbd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags      = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = &_vertices[0];
    _d3device->Get()->CreateBuffer(&vbd, &vinitData, _vb.GetAddressOf());
}

} // namespace graphics