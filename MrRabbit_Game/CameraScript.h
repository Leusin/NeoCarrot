/// 2024-01-10

#pragma once

#include "IComponent.h"
namespace game
{

class CameraScript : public core::IComponent
{
public:
    CameraScript();
    ~CameraScript();

    void Update() override
};

} // namespace game