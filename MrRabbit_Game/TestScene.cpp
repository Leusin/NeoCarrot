#include "TestScene.h"

#include "EntityEnum.h"
#include "EntityManager.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

game::TestScene::TestScene(EntityManager* entityManager) : _name{"test secne"}, _entityManager{entityManager}
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

std::shared_ptr<game::IScene> game::TestScene::NextSene()
{
    return nullptr;
}

} // namespace game