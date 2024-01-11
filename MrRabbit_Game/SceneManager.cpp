#include "SceneManager.h"

#include "IScene.h"
#include "TestScene.h"
#include "EntityManager.h"
#include "EntityFactory.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{

SceneManager::SceneManager(  ) 
    : _entityManager{ std::make_unique<core::EntityManager<EntityFactory>>()}
    , _currenScene{ std::make_shared<TestScene>(_entityManager.get()) }
    , _status{ SceneStatus::START }
    , _currentGraphicsInfo{ std::make_unique<data::ForGraphics>() }
{

#ifdef _DEBUG
    std::cout << "\tSceneManager Constructed\n";
#endif // _DEBUG
}

SceneManager::~SceneManager()
{
#ifdef _DEBUG
    std::cout << "\tSceneManager Distructed\n";
#endif // _DEBUG
}

void SceneManager::Initialize()
{
}

void SceneManager::Update(float deltaTime)
{
    switch (_status)
    {
        case SceneStatus::UNKNOWN:
            break;
        case SceneStatus::LOAD:
            break;
        case SceneStatus::START:
            _currenScene->Initialize();
            _status = SceneStatus::RUN;
            break;
        case SceneStatus::RUN:
            _currenScene->Update(deltaTime);
            _currenScene->ExportData(_currentGraphicsInfo.get());
            break;
        case SceneStatus::FINAL:
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
        case SceneStatus::QUIT:
            break;
        default:
            break;
    }
}

void SceneManager::Finalize()
{
}

void SceneManager::ExportData(data::ForGraphics* info)
{
    info->_camera = _currentGraphicsInfo->_camera;
}

}