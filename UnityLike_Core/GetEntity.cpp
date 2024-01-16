#include "GetEntity.h"

#include <cassert>

namespace core
{
GetEntity::GetEntity(EntityPtr entity) 
    : _entity(EntityPtr(entity))
{
    assert(!_entity.expired() && "엔티티를 가져올 수 없음");
}
EntityPtr GetEntity::Get()
{
    assert(!_entity.expired() && "엔티티를 가져올 수 없음");

    return _entity.lock();
}
const size_t GetEntity::GetId()
{
    return Get()->_id;
}
const std::string GetEntity::GetName()
{
    return Get()->_name;
}
Tag GetEntity::GetTag()
{
    return Get()->_tag;
}
Layer GetEntity::GetLayer()
{
    return Get()->_layer;
}
} // namespace core