#pragma once

#include "IComponent.h"
#include "GetEntity.h"
#include "D3Devices.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>
#include <cassert>

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
    vinitData.pSysMem = &_vertices[0];
    _d3device->GetDevice()->CreateBuffer(&vbd, &vinitData, _vb.GetAddressOf());

}

} // namespace graphics