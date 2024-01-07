#include "TestScene.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

game::TestScene::TestScene()
{
#ifdef _DEBUG
    std::cout << "\t\tTestcene Constructed\n";
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
}

void game::TestScene::Update(float deltaTime)
{
}

void game::TestScene::Finalize()
{
}

std::shared_ptr<game::IScene> game::TestScene::NextSene()
{
    return nullptr;
}