#include "Camera.h"

#include "Entity.h"
#include "Transform.h"
#include "Constants.h"

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

float Camera::GetFovY() const
{
    return 0.f;
}

void Camera::LookAt(const math::Vector3<float>& pos, const math::Vector3<float>& target, const math::Vector3<float>& up)
{
    //math::Vector3<float> L = (target - pos).Normalize();
}

math::Matrix Camera::View() const
{
    return math::Matrix();
}

math::Matrix Camera::Proj() const
{
    return math::Matrix();
}

math::Matrix Camera::ViewProj() const
{
    return math::Matrix();
}


void Camera::Strafe(float distance)
{
    //_position += distance * _look;

    // Transfom 에서 위치 정보, 회전 정보를 가져온다

    // Set Position 한다.
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