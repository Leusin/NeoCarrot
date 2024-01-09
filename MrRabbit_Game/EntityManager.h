/// Object.h : Entity(Game Obejct)를 관리하는 클래스입니다.
///
/// 2024-01-06

#pragma once

#include "EntityEnum.h"

#include <vector>
#include <memory>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr = std::shared_ptr<core::Entity<game::Tag, game::Layer>>;

namespace game
{
class EntityFactory;

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

    EntityPtr CreateEntity(game::Entity enumTypeEntity, const char* name);

private:
    EntityPtr CreateEntity(game::Entity enumTypeEntity, const size_t&& id, const char* name);

    std::vector<std::shared_ptr<core::Entity<Tag, Layer>>> _entities;
    std::unique_ptr<EntityFactory> _factory;
};

} // namespace game