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
math::Vector3<float> Transform::GetPosition()
{
    return _position;
}
math::Vector3<float> Transform::GetRight()
{
    return _right;
}
} // namespace game