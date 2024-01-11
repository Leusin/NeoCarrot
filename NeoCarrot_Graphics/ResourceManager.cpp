#include "ResourceManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ResourceManager::ResourceManager() 
	: _entityManager{std::make_unique<core::EntityManager<ModelFactory>>()}
{
#ifdef _DEBUG
    std::cout << "\tResourceManager Constructed\n";
#endif // _DEBUG
}

void ResourceManager::Initialize()
{
    CreateEnity();

    _entityManager->Initialize();
}

void ResourceManager::Update(float deltaTime)
{
    _entityManager->Update(deltaTime);
}

void ResourceManager::Finalize()
{
    _entityManager->Finalize();
}

void ResourceManager::CreateEnity()
{
    _entityManager->AddEntity(core::GameObect::BOX, "box");
}

}