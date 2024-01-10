#include "Camera.h"

#include "Constants.h"
#include "Entity.h"
#include "Matrix.h"
#include "Transform.h"
#include "Vector3.h"

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace game
{
Camera::Camera(EntityPtr entityPtr) : _transform(entityPtr->GetComponent<Transform>())
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
    //_position += d * _look
    math::Vector3<float> s{distance, distance, distance};
    math::Vector3<float> r{_transform->GetRight()};
    math::Vector3<float> p{_transform->GetPosition()};
    p.MutiplyAdd(s, r, p);

    _transform->SetPosition(p);
}

void Camera::Walk(float distance)
{
    //_position += distance * _right;
    math::Vector3<float> s{distance, distance, distance};
    math::Vector3<float> l{_transform->GetLook()};
    math::Vector3<float> p{_transform->GetPosition()};
    p.MutiplyAdd(s, l, p);

    _transform->SetPosition(p);
}

void Camera::Pitch(float angle)
{
    // 상향 벡터(y)와 시선 벡터(z) 를 오른쪽 벡터(x)애 대해 회전한다
    math::Vector3<float> right{_transform->GetRight()};
    math::Matrix<float>  r;
    r.RotateAxisNormal(right, angle);

    math::Vector3<float> up{_transform->GetUp()};
    math::Vector3<float> look{_transform->GetLook()};

    up.Vector3TransformNormal(r);
    look.Vector3TransformNormal(r);

    _transform->SetUp(up);
    _transform->SetLook(look);
}

void Camera::RotateY(float angle)
{
    // 기저 벡터를 월드 y 축에 대해 회전한다
    math::Matrix<float>  r;
    r.RotateY(angle);

    math::Vector3<float> right{_transform->GetRight()};
    math::Vector3<float> up{_transform->GetUp()};
    math::Vector3<float> look{_transform->GetLook()};

    right.Vector3TransformNormal(r);
    up.Vector3TransformNormal(r);
    look.Vector3TransformNormal(r);

    _transform->SetUp(right);
    _transform->SetUp(up);
    _transform->SetLook(look);
}

} // namespace game