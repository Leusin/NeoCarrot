#include "Camera.h"

#include "Entity.h"
#include "Transform.h"
#include "Constants.h"
#include "Matrix.h"
#include "Vector3.h"

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Camera::Camera(EntityPtr entityPtr) : 
    _transform(entityPtr->GetComponent<Transform>())
{
    assert(_transform);
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Component\n";
#endif // _DEBUG
}

Camera::~Camera()
{
}

void Camera::Update(float dt)
{
}

void Camera::Strafe(float distance)
{
    math::Vector3<float> s{ distance, distance, distance };
    math::Vector3<float> r{ _transform->GetRight() };
    math::Vector3<float> p{_transform->GetPosition()};
    p.MutiplyAdd(s, r, p);
}

void Camera::Walk(float distance)
{
    //_position += distance * _right;
}

void Camera::Pitch(float angle)
{
}

void Camera::RotateY(float angle)
{
}

} // namespace game