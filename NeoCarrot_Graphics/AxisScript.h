#pragma once

#include "IComponent.h"
#include "EntityEnum.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace core
{
template<typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
template<typename V>
class VertexBuffer;
class IndexBuffer;
struct PosCol;

class AxisScript : public core::IComponent
{

public:
    AxisScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    EntityWeakPtr _entity;
    IndexBuffer* _indexBuffer;
    VertexBuffer<PosCol>* _vertexBuffer;
};

} // namespace graphics