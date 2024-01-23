#include "ConstBufferWVP.h"

#include "InputLayouts.h"
#include "Transpose_mk2.h"

#include <directxmath.h>
#include <cassert>

namespace graphics
{
ConstBufferWVP::ConstBufferWVP(EntityPtr entityPtr)
    : ConstantBuffer<ContWorldViewProj>(EntityPtr(entityPtr))
{
}

void ConstBufferWVP::Awake()
{
    ConstantBuffer<ContWorldViewProj>::Awake();
}

void ConstBufferWVP::Update(float dt)
{
    UpdateVariable();
    ConstantBuffer<ContWorldViewProj>::Update(dt);
}

//////////////////////////////////////////////////////////////////////
void ConstBufferWVP::UpdateVariable()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    auto* Trans         = GetComponent<Transpose_mk2>();

    assert(Trans);

    ContWorldViewProj cb;
    cb.WorldViewProj = DirectX::XMMatrixTranspose(Trans->GetWorldViewProj());
    deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

} // namespace graphics