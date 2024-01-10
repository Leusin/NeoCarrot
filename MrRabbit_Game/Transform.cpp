#include "Transform.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Transform::Transform()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Transform Component\n";
#endif // _DEBUG
}

Transform::~Transform()
{
}
math::Vector3<float> Transform::GetPosition() const
{
    return _position;
}
math::Vector3<float> Transform::GetRight() const
{
    return _right;
}

math::Vector3<float> Transform::GetLook() const
{
    return _look;
}

math::Vector3<float> Transform::GetUp() const
{
    return _up;
}

void Transform::SetPosition(const math::Vector3<float>& val)
{
    _position = val;
}

void Transform::SetRight(const math::Vector3<float>& val)
{
    _right = val;
}

void Transform::SetLook(const math::Vector3<float>& val)
{
    _look = val;
}

void Transform::SetUp(const math::Vector3<float>& val)
{
    _up = val;
}

} // namespace game