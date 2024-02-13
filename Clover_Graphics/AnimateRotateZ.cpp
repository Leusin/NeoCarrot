#include "AnimateRotateY.h"

#include "Transpose_mk2.h"

#ifdef _DEBUG
#include <iostream>
#include "AnimateRotateZ.h"
#endif // _DEBUG

namespace graphics
{

AnimateRotateZ::AnimateRotateZ(EntityPtr entityPtr, float speed)
    : GetEntity{ EntityPtr(entityPtr) }
    , _transpose{ GetComponent<Transpose_mk2>() }
    , _speed(speed)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd AnimateRotateY Component\n";
#endif // _DEBUG;
}

void AnimateRotateZ::Update(float dt)
{
    UpdateTick(dt);
    UpdateRotation();
}

void AnimateRotateZ::UpdateTick(float dt)
{
    _t += dt * _speed;
}

void AnimateRotateZ::UpdateRotation()
{
    _transpose->SetWorld(DirectX::XMMatrixRotationZ(_t));
}

} // namespace graphics