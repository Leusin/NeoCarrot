/// 2024-01-09

#pragma once

#include "IScene.h"

#include <string>
#include <vector>

namespace game
{
class EntityManager;

class TestScene : public IScene
{
public:
    TestScene(EntityManager* entityManager);
    ~TestScene();

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;


    std::shared_ptr<IScene> NextSene() override;

public:
    const std::string _name;

private:
    void           CreateEnity();

    EntityManager* _entityManager;
};

} // namespace game