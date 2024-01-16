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
    assert(_d3device && "IndexBuffer ���� D3Devices �� ã�� �� ����");

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
    // �а� �ִ� �޽��� ���� ũ��
    UINT idxCount = static_cast<UINT>(data.faces.size());

    // �а� �ִ� �Žð� ���۵� �ε��� ����
    _indexOffset.emplace_back(_totalIndexCount);

    // �а� �ִ� �޽ð� ���� �� �ε��� ��
    _indexCount.emplace_back(3 * idxCount);

    // ��ü �ε��� ��
    _totalIndexCount += (3 * idxCount);

    for (UINT i = 0; i < idxCount; ++i)
    {
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[0]));
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[1]));
        _indices.emplace_back(static_cast<UINT>(data.faces[i].indices[2]));
    }
}

} // namespace graphics