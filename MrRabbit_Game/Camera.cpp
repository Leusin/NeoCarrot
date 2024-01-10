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

    //
    // _view 업데이트
    //
    math::Vector3<float> r = _transform->GetRight();
    math::Vector3<float> u = _transform->GetUp();
    math::Vector3<float> l = _transform->GetLook();
    math::Vector3<float> p = _transform->GetPosition();

    float x = -p.Dot(r);
    float y = -p.Dot(u);
    float z = -p.Dot(l);

    _cInfo._view[0][0] = _transform->GetRight().x;
    _cInfo._view[1][0] = _transform->GetRight().y;
    _cInfo._view[2][0] = _transform->GetRight().z;
    _cInfo._view[3][0] = x;

    _cInfo._view[0][1] = _transform->GetUp().x;
    _cInfo._view[1][1] = _transform->GetUp().y;
    _cInfo._view[2][1] = _transform->GetUp().z;
    _cInfo._view[3][1] = y;

    _cInfo._view[0][2] = _transform->GetLook().x;
    _cInfo._view[1][2] = _transform->GetLook().y;
    _cInfo._view[2][2] = _transform->GetLook().z;
    _cInfo._view[3][2] = z;

    _cInfo._view[0][3] = 0.0f;
    _cInfo._view[1][3] = 0.0f;
    _cInfo._view[2][3] = 0.0f;
    _cInfo._view[3][3] = 1.0f;
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