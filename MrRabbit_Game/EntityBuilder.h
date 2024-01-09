#pragma once

#include "EntityEnum.h"

#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<game::Tag, game::Layer>>;

namespace game
{

class EntityBuilder
{
public:
    EntityBuilder(const size_t&& id, const char* name, Tag&& tag, Layer&& layer);

public:
    // 제품 조립
    EntityBuilder AddTransform();

    // 제품 반환
    EntityPtr     Build();

private:
    EntityPtr _entity;
};

} // namespace game