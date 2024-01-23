#pragma once

#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{
class Transpose_mk2;

// º»¹®
class ColoredBox2Script: public core::IComponent, virtual core::GetEntity
{
public:
    ColoredBox2Script(EntityPtr entityPtr);

    void Update(float dt) override;


private:
    void UpdateTick(float dt);
    void UpdateAnimation();

private:
    Transpose_mk2* _transpose;
    float _t1{ 0.0f };
    float _t2{ 0.0f };
};

} // namespace graphics