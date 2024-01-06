#include "SceneManager.h"

#include "IScene.h"
#include "TestScene.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


game::SceneManager::SceneManager() : _currenScene(std::make_shared<TestScene>())
{
#ifdef _DEBUG
    std::cout << "\tSceneManager Constructed\n";
#endif // _DEBUG
}

game::SceneManager::~SceneManager()
{
#ifdef _DEBUG
    std::cout << "\tSceneManager Distructed\n";
#endif // _DEBUG
}

void game::SceneManager::Initialize()
{
}

void game::SceneManager::Update()
{
    switch (_status)
    {
        case game::SceneStatus::UNKNOWN:
            break;
        case game::SceneStatus::LOAD:
            break;
        case game::SceneStatus::START:
            _currenScene->Initialize();
            _status = SceneStatus::RUN;
            break;
        case game::SceneStatus::RUN:
            _currenScene->Update();
            _status = SceneStatus::FINAL;
            break;
        case game::SceneStatus::FINAL:
        {
            _currenScene->Finalize();
            std::weak_ptr<IScene> nextScene = _currenScene->NextSene();
            if (!nextScene.expired())
            {
                _currenScene = nextScene.lock();
                _status      = SceneStatus::START;
            }
            else
            {
                _status = SceneStatus::QUIT;
            }
        }
        break;
        case game::SceneStatus::QUIT:
            break;
        default:
            break;
    }
}

void game::SceneManager::Finalize()
{
}
