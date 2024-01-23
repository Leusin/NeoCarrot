#pragma once

#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{
class Transpose_mk2;

// º»¹®
class AnimateRotateY: public core::IComponent, virtual core::GetEntity
{
public:
    AnimateRotateY(EntityPtr entityPtr, float speed);

    void Update(float dt) override;


private:
    void UpdateTick(float dt);
    void UpdateRotation();

private:
    Transpose_mk2* _transpose;
    float _tick{ 0.0f };
    float _speed{ 0.0f };
};

} // namespace graphics