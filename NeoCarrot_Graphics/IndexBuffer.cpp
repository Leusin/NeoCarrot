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

} // namespace graphics