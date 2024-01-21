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
Camera::Camera(EntityPtr entityPtr) 
    : _transform(entityPtr->GetComponent<Transform>())
    , _cameraInfo{}
{
    assert(_transform && "camera 가 transform 정보를 불러올 수 없음");
    
    //
    // _cameraInfo
    // 해당 구조체의 초기값과 같지만
    // 명시적으로 초기화
    //

    _cameraInfo._position = { 0.0f, 0.0f, 0.0f };

    _cameraInfo._right = { 1.0f, 0.f, 0.f };
    _cameraInfo._up = { 0.0f, 1.f, 0.f };
    _cameraInfo._look = { 0.0f, 0.f, 1.f };

    _cameraInfo._nearZ = 000.1f;
    _cameraInfo._farZ = 1000.f;
    _cameraInfo._fovY  = 0.25f;


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

    _cameraInfo._view[0][0] = _transform->GetRight().x;
    _cameraInfo._view[1][0] = _transform->GetRight().y;
    _cameraInfo._view[2][0] = _transform->GetRight().z;
    _cameraInfo._view[3][0] = x;

    _cameraInfo._view[0][1] = _transform->GetUp().x;
    _cameraInfo._view[1][1] = _transform->GetUp().y;
    _cameraInfo._view[2][1] = _transform->GetUp().z;
    _cameraInfo._view[3][1] = y;

    _cameraInfo._view[0][2] = _transform->GetLook().x;
    _cameraInfo._view[1][2] = _transform->GetLook().y;
    _cameraInfo._view[2][2] = _transform->GetLook().z;
    _cameraInfo._view[3][2] = z;

    _cameraInfo._view[0][3] = 0.0f;
    _cameraInfo._view[1][3] = 0.0f;
    _cameraInfo._view[2][3] = 0.0f;
    _cameraInfo._view[3][3] = 1.0f;

    //
    // _position
    //

    _cameraInfo._position = _transform->GetPosition();
    _cameraInfo._look = _transform->GetLook();
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

    up = up.Vector3TransformNormal(r);
    look = look.Vector3TransformNormal(r);

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

    right = right.Vector3TransformNormal(r);
    up = up.Vector3TransformNormal(r);
    look = look.Vector3TransformNormal(r);

    _transform->SetUp(right);
    _transform->SetUp(up);
    _transform->SetLook(look);
}

data::CameraInfo Camera::GetCameraInfo()
{
    return _cameraInfo;
}

} // namespace game