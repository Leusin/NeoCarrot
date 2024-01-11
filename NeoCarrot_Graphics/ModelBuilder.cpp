#include "ModelBuilder.h"

#include "Entity.h"
#include "D3Device.h"
#include "Transpose.h"
#include "VertexBuffer.h"
#include "VertexStruct.h"
#include "IndexBuffer.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
#include <d3d11.h>


namespace graphics
{
    
ModelBuilder::ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer) :
_entity(std::make_shared<core::Entity<core::Tag, core::Layer>>(std::forward<const size_t>(id),
                                                               std::move(name),
                                                               std::move(tag),
                                                               std::move(layer)))
{
#ifdef _DEBUG
    std::cout << "\t\t\tCreate Graphics Entity ( " << name << ", " << static_cast<int>(id) << " ) \n";
#endif // _DEBUG
}
ModelBuilder ModelBuilder::AddD3Device(ID3D11Device* device, ID3D11DeviceContext* dContext)
{
    _entity->AddComponent<D3Device>(device, dContext);

    return *this;
}

ModelBuilder ModelBuilder::AddTransform()
{
    _entity->AddComponent<Transpose>();

    return *this;
}

ModelBuilder ModelBuilder::AddVertexBuffer()
{
    _entity->AddComponent<VertexBuffer<graphics::Pos>>(_entity);

    return *this;
}

ModelBuilder ModelBuilder::AddIndexBuffer()
{
    _entity->AddComponent<IndexBuffer>(_entity);

    return *this;
}

EntityPtr ModelBuilder::Build()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tEnd build\n";
#endif // _DEBUG

    return _entity;
}

} // namespace graphics