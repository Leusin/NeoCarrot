#pragma once

#include "EntityEnum.h"
#include "Entity.h"
#include "VertexBuffer.h"

#include <memory>
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;

/*
namespace core
{
template <typename T, typename U>
class Entity;
} // namespace core
*/

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{

class ModelBuilder
{
public:
    ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer);
    
    ModelBuilder AddD3Device(ID3D11Device* device, ID3D11DeviceContext* dContext);
    
    ModelBuilder AddTransform();
    
    template <typename T>
    ModelBuilder AddVertexBuffer();

    ModelBuilder AddIndexBuffer();

    ModelBuilder AddEffect(std::wstring fileName);

    ModelBuilder AddVertexLayout(const D3D11_INPUT_ELEMENT_DESC* desc);

    // 제품 반환
    EntityPtr Build();

private:

    EntityPtr _entity;
};

template <typename T>
inline ModelBuilder ModelBuilder::AddVertexBuffer()
{
    _entity->AddComponent<VertexBuffer<T>>(_entity);

    return *this;
}

} // namespace graphics