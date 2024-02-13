#include "AnimateRotateY.h"

#include "Transpose_mk2.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

AnimateRotateY::AnimateRotateY(EntityPtr entityPtr, float speed)
    : GetEntity{ EntityPtr(entityPtr) }
    , _transpose{ GetComponent<Transpose_mk2>() }
    , _speed(speed)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd AnimateRotateY Component\n";
#endif // _DEBUG;
}

void AnimateRotateY::Update(float dt)
{
    UpdateTick(dt);
    UpdateRotation();
}

void AnimateRotateY::UpdateTick(float dt)
{
    _tick += dt * _speed;
}

void AnimateRotateY::UpdateRotation()
{
    _transpose->SetWorld(DirectX::XMMatrixRotationY(_tick));
}

} // namespace graphics