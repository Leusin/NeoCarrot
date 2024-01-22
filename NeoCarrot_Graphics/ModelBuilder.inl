#include "VertexBuffer.h"
#include "VertexResource.h"
#include "ConstantBuffer.h"

namespace graphics
{
template<typename T>
inline ModelBuilder ModelBuilder::AddVertexBuffer()
{
    _entity->AddComponent<VertexBuffer<T>>(_entity);
    return *this;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline ModelBuilder ModelBuilder::AddVertexResource(
    std::wstring shaderFile,
    const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc)
{
    _entity->AddComponent<VertexResource<T>>(_entity, shaderFile, desc);
    return *this;
}

//////////////////////////////////////////////////////////////////////
template<typename T>
inline ModelBuilder ModelBuilder::AddContantBuffer()
{
    _entity->AddComponent<ConstantBuffer<T>>(_entity);
    return *this;
}

} // namespace graphics