/// 2024-01-15
#pragma once

#include "EntityEnum.h"
#include "Entity.h"

#include <memory>

/*
namespace core
{
template <typename T, typename U>
class Entity;
}
*/

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace core
{

class GetEntity
{
private:
    GetEntity(EntityPtr entity);

    template <typename T>
    T* GetComponent();

    EntityPtr    Get();

    const size_t       GetId();
    const std::string GetName();
    Tag GetTag();
    Layer GetLayer();

private:
    EntityWeakPtr _entity;
};

////////////////////////////////////////////////////////////
template <typename T>
inline T* GetEntity::GetComponent()
{
    return _entity.lock()->GetComponent<T>();
}

} // namespace core