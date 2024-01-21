/// 2024-01-15
#pragma once

#include "Entity.h"
#include "EntityEnum.h"

#include <memory>

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace core
{

class GetEntity
{
public:
    GetEntity(EntityPtr entity);

    template<typename T>
    T* GetComponent();

    EntityPtr Get();

    const size_t GetId();
    const std::string GetName();
    Tag GetTag();
    Layer GetLayer();

private:
    EntityWeakPtr _entity;
};

//////////////////////////////////////////////////////////////////////
template<typename T>
inline T* GetEntity::GetComponent()
{
    return _entity.lock()->GetComponent<T>();
}

} // namespace core