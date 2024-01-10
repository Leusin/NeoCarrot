#include "Camera.h"

#include "Constants.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Camera::Camera()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Camera Component\n";
#endif // _DEBUG
}
Camera::~Camera()
{
}
math::Vector3<float> Camera::GetPosition() const
{
    return _position;
}
void Camera::SetPosition(float x, float y, float z)
{
    //_position = (x, y, z);
}
void Camera::SetPosition(const math::Vector3<float>& pos)
{
    _position = pos;
}
math::Vector3<float> Camera::GetRight() const
{
    return _right;
}
math::Vector3<float> Camera::GetUp() const
{
    return _up;
}
math::Vector3<float> Camera::GetLook() const
{
    return _look;
}

float Camera::GetAspect() const
{
    return _aspect;
}

float Camera::GetFovY() const
{
    return _fovY;
}

float Camera::GetFovX() const
{
    float halfWidth = 0.5f * GetNearWindowHeight();
    return 2.0f * atanf(halfWidth / _nearZ);
}

float Camera::GetNearWindowWidth() const
{
    return _aspect * _nearWindowHeight;
}

float Camera::GetNearWindowHeight() const
{
    return _nearWindowHeight;
}

float Camera::GetFarWindowWidth() const
{
    return _aspect * _farWindowHeight;
}

float Camera::GetFarWindowHeight() const
{
    return _farWindowHeight;
}

void Camera::SetLens(float fovY, float aspect, float zn, float zf)
{
    _fovY   = fovY * math::constant::PI;
    _aspect = aspect;

    _nearZ = zn;
    _farZ  = zf;

    _nearWindowHeight = 2.0f * _nearZ * tanf(0.5f * _fovY);
    _farWindowHeight  = 2.0f * _farZ * tanf(0.5f * _fovY);
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
    _position += distance * _look;
}

void Camera::Walk(float distance)
{
    _position += distance * _right;
}

void Camera::Pitch(float angle)
{
}

void Camera::RotateY(float angle)
{
}

} // namespace game