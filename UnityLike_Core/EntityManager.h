/// Object.h : Entity(Game Obejct)를 관리하는 클래스입니다.
///
/// 2024-01-06

#pragma once

#include "Entity.h"
#include "EntityEnum.h"
#include "IFactory.h"

#ifdef _DEBUG
#include <iostream>
#endif

#include <memory>
#include <vector>
#include <cassert>

namespace core
{

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using WeakEntityPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

//class IFactory;

template <typename T>
class EntityManager
{
public:
    template <typename... Args>
    EntityManager(Args&&... args);

    void Initialize();
    void Update(float deltaTime);
    void Finalize();

    void AddEntity(GameObect enumTypeEntity, const char* name);

    [[nodiscard]] WeakEntityPtr GetEntity(const char* name);

    [[nodiscard]] WeakEntityPtr GetEntity(const size_t&& id);

    [[nodiscard]] std::vector<WeakEntityPtr> GetEntity(core::Tag enumTag);

private:
    EntityPtr CreateEntity(GameObect enumTypeEntity, const size_t&& id, const char* name);
    EntityPtr CreateEntity(GameObect enumTypeEntity, const char* name);

    void AddEntity(EntityPtr entityPtr);

    std::vector<EntityPtr>    _entities;
    std::unique_ptr<T> _factory;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
template <typename... Args>
inline EntityManager<T>::EntityManager(Args&&... args) 
    : _factory(std::make_unique<T>(std::forward<Args>(args)...))
{

#ifdef _DEBUG
    std::cout << "\tEntityManager Constructed\n";
#endif // _DEBUG
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void EntityManager<T>::Initialize()
{
    for (auto& e : _entities)
    {
        e->Awake();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void EntityManager<T>::Update(float deltaTime)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void EntityManager<T>::Finalize()
{
    for (auto& e : _entities)
    {
        e->Destroy();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void EntityManager<T>::AddEntity(GameObect enumTypeEntity, const char* name)
{
    auto entity = CreateEntity(enumTypeEntity, std::move(name));
    AddEntity(entity);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline WeakEntityPtr EntityManager<T>::GetEntity(const char* name)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline WeakEntityPtr EntityManager<T>::GetEntity(const size_t&& id)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline std::vector<WeakEntityPtr> EntityManager<T>::GetEntity(core::Tag enumTag)
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline EntityPtr EntityManager<T>::CreateEntity(GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    return _factory->CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline EntityPtr EntityManager<T>::CreateEntity(GameObect enumTypeEntity, const char* name)
{
    auto id = _entities.size();
    return CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void EntityManager<T>::AddEntity(EntityPtr entityPtr)
{
    _entities.emplace_back(entityPtr);
}
} // namespace core

//#include "EntityManager.inl"