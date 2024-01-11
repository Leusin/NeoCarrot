/// EntityManager.h : 그래픽스 엔진에서의 엔티티를 관리합니다.
///
/// 2024-01-11

#pragma once

#include "ModelEnum.h"

#include <memory>
#include <vector>

namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<grahics::Tag, grahics::Layer>>;
using WeakEntityPtr = std::weak_ptr<core::Entity<grahics::Tag, grahics::Layer>>;

namespace grahics
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

    //void AddEntity(grahics::Entity enumTypeEntity, const char* name);

    [[nodiscard]] WeakEntityPtr GetEntity(const char* name);

    [[nodiscard]] WeakEntityPtr GetEntity(const size_t&& id);

    [[nodiscard]] std::vector<WeakEntityPtr> GetEntity(grahics::Tag enumTag);

private:
    //EntityPtr CreateEntity(grahics::Model enumTypeEntity, const size_t&& id, const char* name);
    //EntityPtr CreateEntity(grahics::Model enumTypeEntity, const char* name);

    void AddEntity(EntityPtr entityPtr);

    std::vector<EntityPtr>         _entities;
    std::unique_ptr<EntityFactory> _factory;
};

} // namespace grahics