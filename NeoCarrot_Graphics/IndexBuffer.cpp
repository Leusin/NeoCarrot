#include "IndexBuffer.h"

#include "D3Devices.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
IndexBuffer::IndexBuffer(EntityPtr entityPtr) 
    : GetEntity(EntityPtr(entityPtr))
    , _d3device{GetComponent<graphics::D3Devices>()}
{
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
    iinitData.pSysMem = &_indices[0];
    _d3device->GetDevice()->CreateBuffer(&ibd, &iinitData, _ib.GetAddressOf());
}

} // namespace graphics