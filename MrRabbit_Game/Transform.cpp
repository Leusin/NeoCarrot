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
void Transform::Update(float dt)
{
    math::Vector3<float> r = GetRight();
    math::Vector3<float> u = GetUp();
    math::Vector3<float> l = GetLook();
    math::Vector3<float> p = GetPosition();
	
	//
    // 오른쪽, 상향, 시선 벡터 정규직교화
    //

	l = l.Normalize();
    u = l.Cross(r);
    u = u.Normalize();
    r = u.Cross(l);

	//
    // 시야 행렬을 채운다
    //

	SetRight(r);
    SetUp(u);
    SetLook(l);
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