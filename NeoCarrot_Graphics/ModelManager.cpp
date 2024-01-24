#include "ModelManager.h"

#include "Camera3D.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

ModelManager::ModelManager(D3D11Context_mk2* d3dcontext, Camera3D* camera)
    : _entityManager{ std::make_unique<core::EntityManager<ModelFactory>>(d3dcontext, camera) }
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
    CreateEnity(core::GameObect::AXIS, "axis");
    CreateEnity(core::GameObect::GRID, "grid");

    //CreateEnity(core::GameObect::BOX, "box");
    //CreateEnity(core::GameObect::TUTORIAL04, "colored box1");
    //CreateEnity(core::GameObect::TUTORIAL05, "colored box2");
    //CreateEnity(core::GameObect::LIGHTBOX1, "light box1");
    CreateEnity(core::GameObect::TUTORIAL06, "light box");
}

void ModelManager::CreateEnity(const core::GameObect&& enumTypeEntity,
                               const char* name)
{
    _entityManager->AddEntity(enumTypeEntity, name);
}

} // namespace graphics