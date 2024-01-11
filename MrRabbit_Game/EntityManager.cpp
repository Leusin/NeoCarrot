#include "EntityManager.h"

#include "../UnityLike_Core/Entity.h"
#include "EntityFactory.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

EntityManager::EntityManager() : _factory{std::make_unique<EntityFactory>()}
{
#ifdef _DEBUG
    std::cout << "\tEntityManager Constructed\n";
#endif // _DEBUG
}

EntityManager::~EntityManager()
{
#ifdef _DEBUG
    std::cout << "\tEntityManager Distructed\n";
#endif // _DEBUG
}

void EntityManager::Initialize()
{
    for (auto& e : _entities)
    {
        e->Awake();
    }
}

void EntityManager::Update(float deltaTime)
{

    for (auto& e : _entities)
    {
        if (e->_isStart)
        {
            e->Start();
            e->_isActive = true;
            e->_isStart  = false;
        }
        else if (e->_isActive && !e->_isStart)
        {
            e->Update(deltaTime);
            e->FixedUpdate(deltaTime);
            e->LateUpdate(deltaTime);
            e->OnEnable();
        }
        else if (!e->_isActive && !e->_isStart)
        {
            e->OnDisable();
        }
    }
}

void EntityManager::Finalize()
{
    for (auto& e : _entities)
        e->Destroy();
}

void EntityManager::AddEntity(game::Entity enumTypeEntity, const char* name)
{
    auto entity = CreateEntity(enumTypeEntity, std::move(name));
    AddEntity(entity);
}

WeakEntityPtr EntityManager::GetEntity(const char* name)
{

    for (auto& e : _entities)
    {
        if (e->_name == name)
        {
            return e;
        }

    }

    return WeakEntityPtr();
}

WeakEntityPtr EntityManager::GetEntity(const size_t&& id)
{
    // id는 0 부터 추가된다.
    // id 따라서 엔티티 크기보다 크면 안된다.
    assert(_entities.size() < id && "유효하지 않는 id값");

    for (auto& e : _entities)
    {
        if (e->_id == id)
        {
            return e;
        }
    }

    return WeakEntityPtr();
}

std::vector<WeakEntityPtr> EntityManager::GetEntity(game::Tag enumTag)
{
    std::vector<WeakEntityPtr> spisificEntitis;

    for (auto& e : _entities)
    {
        if (e->_tag == enumTag)
        {
            spisificEntitis.emplace_back(e);
        }
    }

    return spisificEntitis;
}

EntityPtr EntityManager::CreateEntity(game::Entity enumTypeEntity, const size_t&& id, const char* name)
{
    return _factory->CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}

EntityPtr EntityManager::CreateEntity(game::Entity enumTypeEntity, const char* name)
{
    auto id = _entities.size();
    return CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}
void EntityManager::AddEntity(EntityPtr entityPtr)
{
    _entities.emplace_back(entityPtr);
}
/*
/////////////////////////////////////////////////////////////////////////////////
EntityPtr EntityManager::CreateEntity(const char* name, Tag&& tag, Layer&& layer)
{
#ifdef _DEBUG
    std::cout << "\t\tCreate Entity ( " << name << " ) \n";
#endif // _DEBUG

    auto id = _entities.size();

    return std::make_shared<core::Entity<Tag, Layer>>(std::forward<const size_t>(id),
                                                      std::move(name),
                                                      std::move(tag),
                                                      std::move(layer));
}

/////////////////////////////////////////////////////////////////////////////////
void EntityManager::AddeEntity(EntityPtr& entity)
{
#ifdef _DEBUG
    std::cout << "\t\tAdd Entity ( " << entity->_name << " ) \n";
#endif // _DEBUG

    _entities.emplace_back(entity);
}

/////////////////////////////////////////////////////////////////////////////////
void EntityManager::AddeEntity(const char* name, Tag&& tag, Layer&& layer)
{
    auto entity = CreateEntity(std::move(name), std::move(tag), std::move(layer));
    AddeEntity(entity);
}
*/

} // namespace game