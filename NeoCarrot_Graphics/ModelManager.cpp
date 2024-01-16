#include "ModelManager.h"

#include "Camera3D.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ModelManager::ModelManager(D3D11Context_mk2* d3dcontext, Camera3D* camera) 
    : _entityManager{std::make_unique<core::EntityManager<ModelFactory>>(d3dcontext, camera)}
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
    _entityManager->AddEntity(core::GameObect::GRID, "grid");
    _entityManager->AddEntity(core::GameObect::BOX, "box");
}

}          