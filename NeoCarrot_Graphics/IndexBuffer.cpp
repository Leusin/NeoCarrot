#include "IndexBuffer.h"

#include "D3Devices.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <cassert>

namespace graphics
{
IndexBuffer::IndexBuffer(EntityPtr entityPtr) 
    : GetEntity(EntityPtr(entityPtr))
    , _d3device{GetComponent<graphics::D3Devices>()}
{
    assert(_d3device && "IndexBuffer 에서 D3Devices 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd IndexBuffer Component\n";
#endif // _DEBUG
}
void IndexBuffer::Awake()
{
    if (_indices.empty()) return;

    D3D11_BUFFER_DESC ibd;
    ibd.Usage          = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth      = sizeof(UINT) * static_cast<UINT>(_indices.size());
    ibd.BindFlags      = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags      = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = _indices.data();

    _d3device->GetDevice()->CreateBuffer(&ibd, &iinitData, _ib.GetAddressOf());
}

void IndexBuffer::SetFromMesh(const model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    UINT idxCount = static_cast<UINT>(data.faces.size());

    // 읽고 있는 매시가 시작될 인덱스 숫자
    _indexOffset.emplace_back(_totalIndexCount);

    // 읽고 있는 메시가 가질 총 인덱스 수
    _indexCount.emplace_back(3 * idxCount);

    // 전체 인덱스 수
    _totalIndexCount += (3 * idxCount);

    for (UINT i = 0; i < idxCount; ++i)
    {
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[0]));
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[1]));
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[2]));
    }
}

} // namespace graphics