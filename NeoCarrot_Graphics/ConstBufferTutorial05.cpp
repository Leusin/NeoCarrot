#include "ConstBufferTutorial05.h"

#include "InputLayouts.h"
#include "Transpose_mk2.h"

#include <directxmath.h>
#include <cassert>

namespace graphics
{
ConstBufferTutorial05::ConstBufferTutorial05(EntityPtr entityPtr)
    : ConstantBuffer<ConstBuffWorldViewProj>(EntityPtr(entityPtr))
{
}

void ConstBufferTutorial05::Awake()
{
    ConstantBuffer<ConstBuffWorldViewProj>::Awake();
}

void ConstBufferTutorial05::Update(float dt)
{
    UpdateVariable();
    ConstantBuffer<ConstBuffWorldViewProj>::Update(dt);
}

//////////////////////////////////////////////////////////////////////
void ConstBufferTutorial05::UpdateVariable()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    auto* Trans         = GetComponent<Transpose_mk2>();

    assert(Trans);

    ConstBuffWorldViewProj cb;
    cb.WorldViewProj = DirectX::XMMatrixTranspose(Trans->GetWorldViewProj());
    deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

} // namespace graphics