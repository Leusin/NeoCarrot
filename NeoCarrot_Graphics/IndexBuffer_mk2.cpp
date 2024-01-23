#include "IndexBuffer_mk2.h"

#include "D3Devices.h"

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

graphics::IndexBuffer_mk2::IndexBuffer_mk2(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
{
    assert(_d3devices && "IndexBuffer_mk2 는 _d3devices를 필요로함");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd IndexBuffer_mk2 Component\n";
#endif // _DEBUG;
}

//////////////////////////////////////////////////////////////////////
void IndexBuffer_mk2::Awake()
{
    InitilaizeVertexBuffer();
}

void IndexBuffer_mk2::Update(float dt)
{
    UpdateInputAssemBler();
}

//////////////////////////////////////////////////////////////////////
void IndexBuffer_mk2::GetIndices(const std::vector<WORD>& indices)
{
    _indices = indices;
}

//////////////////////////////////////////////////////////////////////
void IndexBuffer_mk2::InitilaizeVertexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(WORD) * static_cast<WORD>(_indices.size());
    bd.BindFlags         = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = _indices.data();

    auto* device = _d3devices->GetDevice();
    device->CreateBuffer(&bd, &InitData, _indexBuffer.GetAddressOf());
}

//////////////////////////////////////////////////////////////////////
void IndexBuffer_mk2::UpdateInputAssemBler()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

} // namespace graphics