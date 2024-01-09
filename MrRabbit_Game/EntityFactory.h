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

class EntityFactory
{
public:
    EntityPtr CreateEntity(game::Entity enumTypeEntity, const size_t&& id, const char* name);

private:
    EntityPtr CreateCarEntity(const size_t&& id, const char* name);
};

}