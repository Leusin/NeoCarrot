#include "EntityManager.h"
#include "../UnityLike_Core/Entity.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


game::EntityManager::EntityManager()
{
#ifdef _DEBUG
    std::cout << "\tEntityManager Constructed\n";
#endif // _DEBUG
}

game::EntityManager::~EntityManager()
{
#ifdef _DEBUG
    std::cout << "\tEntityManager Distructed\n";
#endif // _DEBUG
}

void game::EntityManager::Initialize()
{
    for (auto& e : _entities) 
    {
        e->Awake();
    }
}

void game::EntityManager::Update(float deltaTime)
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
            e->Update();
            e->FixedUpdate();
            e->LateUpdate();
            e->OnEnable();
        }
        else if (!e->_isActive && !e->_isStart)
        {
            e->OnDisable();
        }
    }
}

void game::EntityManager::Finalize()
{
    for (auto& e : _entities)e->Destroy();
}
