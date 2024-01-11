#include "TestScene.h"

#include "EntityEnum.h"
#include "EntityManager.h"
#include "GraphicsEngine.h"
#include "CameraManager.h"

#include <cassert>
#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

game::TestScene::TestScene(EntityManager* entityManager) 
    : _name{"test secne"}, 
    _entityManager{entityManager},
    _cameraManager{std::make_unique<CameraManager>()}
{
#ifdef _DEBUG
    std::cout << "\t\tTestScene Constructed\n";
#endif // _DEBUG
}

game::TestScene::~TestScene()
{
#ifdef _DEBUG
    std::cout << "\t\tTestScene Distructed\n";
#endif // _DEBUG
}

void game::TestScene::Initialize()
{
    CreateEnity();
    InitCameraManager();

    _entityManager->Initialize();

}

void game::TestScene::Update(float deltaTime)
{
    _entityManager->Update(deltaTime);
}

void game::TestScene::Finalize()
{
    _entityManager->Finalize();
}

void game::TestScene::CreateEnity()
{
    _entityManager->AddEntity(Entity::CAMERA, "camera");
}

void TestScene::ExportData(data::ForGraphics* info)
{
    _cameraManager->GetActiveCameraInfo(info);
}

std::shared_ptr<game::IScene> game::TestScene::NextSene()
{
    return nullptr;
}

void TestScene::InitCameraManager()
{
    auto cameras = _entityManager->GetEntity(Tag::CAMERA);
    _cameraManager->GetCameraEntitys(cameras);
}

} // namespace game