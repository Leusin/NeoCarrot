#include "EntityManager.h"

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
}

void game::EntityManager::Update()
{
}

void game::EntityManager::Finalize()
{
}
