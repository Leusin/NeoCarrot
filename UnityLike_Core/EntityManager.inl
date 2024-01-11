//#include "EntityManager.h"
//#include "../MrRabbit_Game/EntityFactory.h"
#pragma once

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline EntityManager<T>::EntityManager() : _factory(std::make_unique<T>())
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
    // id�� 0 ���� �߰��ȴ�.
    // id ���� ��ƼƼ ũ�⺸�� ũ�� �ȵȴ�.
    assert(_entities.size() < id && "��ȿ���� �ʴ� id��");

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

  /*
EntityManager::EntityManager() 
    
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

void EntityManager::AddEntity(GameObect enumTypeEntity, const char* name)
{
    auto entity = CreateEntity(enumTypeEntity, std::move(name));
    AddEntity(entity);
}

WeakEntityPtr EntityManager::GetEntity(const char* name)
{

   
}

WeakEntityPtr EntityManager::GetEntity(const size_t&& id)
{
    // id�� 0 ���� �߰��ȴ�.
    // id ���� ��ƼƼ ũ�⺸�� ũ�� �ȵȴ�.
    assert(_entities.size() < id && "��ȿ���� �ʴ� id��");

    for (auto& e : _entities)
    {
        if (e->_id == id)
        {
            return e;
        }
    }

    return WeakEntityPtr();
}

std::vector<WeakEntityPtr> EntityManager::GetEntity(core::Tag enumTag)
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

EntityPtr EntityManager::CreateEntity(core::GameObect enumTypeEntity, const size_t&& id, const char* name)
{
    return _factory->CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}

EntityPtr EntityManager::CreateEntity(core::GameObect enumTypeEntity, const char* name)
{
    auto id = _entities.size();
    return CreateEntity(enumTypeEntity, std::forward<const size_t>(id), std::move(name));
}
void EntityManager::AddEntity(EntityPtr entityPtr)
{
    _entities.emplace_back(entityPtr);
}

*/
