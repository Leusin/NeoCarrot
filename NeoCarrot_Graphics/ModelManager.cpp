#include "ModelManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ModelManager::ModelManager() 
	: _entityManager{std::make_unique<core::EntityManager<ModelFactory>>()}
{
#ifdef _DEBUG
    std::cout << "\tResourceManager Constructed\n";
#endif // _DEBUG
}

void ModelManager::Initialize()
{
    CreateEnity();

    _entityManager->Initialize();
}

void ModelManager::Update(float deltaTime)
{
    _entityManager->Update(deltaTime);
}

void ModelManager::Finalize()
{
    _entityManager->Finalize();
}

void ModelManager::CreateEnity()
{
    _entityManager->AddEntity(core::GameObect::BOX, "box");
}

}