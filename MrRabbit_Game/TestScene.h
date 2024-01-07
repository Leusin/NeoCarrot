#pragma once

#include "IScene.h"

#include <string>

namespace game
{
class TestScene : public IScene
{
public:
    TestScene();
    ~TestScene();

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Finalize() override;

    std::shared_ptr<IScene> NextSene() override;

public:
    const std::string _name{"test secne"};
};

} // namespace game