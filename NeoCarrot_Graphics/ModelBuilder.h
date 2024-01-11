#pragma once

#include "EntityEnum.h"

#include <memory>

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace core
{
template <typename T, typename U>
class Entity;
} // namespace core

using EntityPtr = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{

class ModelBuilder
{
public:
    ModelBuilder(const size_t&& id, const char* name, core::Tag&& tag, core::Layer&& layer);
    
    ModelBuilder AddD3Device(ID3D11Device* device, ID3D11DeviceContext* dContext);
    
    ModelBuilder AddTransform();
    
    ModelBuilder AddVertexBuffer();

    ModelBuilder AddIndexBuffer();

    // 제품 반환
    EntityPtr Build();

private:

    EntityPtr _entity;
};

}