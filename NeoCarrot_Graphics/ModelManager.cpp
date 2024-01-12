#include "ModelManager.h"

#include "Camera3D.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ModelManager::ModelManager(ResourceManager* resourceManager, Camera3D* camera) :
_entityManager{std::make_unique<core::EntityManager<ModelFactory>>(resourceManager, camera)}
{
#ifdef _DEBUG
    std::cout << "\tModelManager Constructed\n";
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
    _entityManager->AddEntity(core::GameObect::AXIS, "axis");
    _entityManager->AddEntity(core::GameObect::BOX, "box");
}

}