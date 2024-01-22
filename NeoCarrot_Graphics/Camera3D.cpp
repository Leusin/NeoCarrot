#include "Camera3D.h"

#include "CameraInfo.h"
#include "Constants.h"
#include "Matrix.h"

using namespace DirectX;
using namespace graphics;

Camera3D::Camera3D()
{
}

graphics::Camera3D::Camera3D(int clientWidth, int clientHeight)
{
    // 화면비
    _aspect = static_cast<float>(clientWidth) / clientHeight;

    // 업데이트
    
}

Camera3D::~Camera3D()
{
}

void graphics::Camera3D::Initialize()
{
    SetLens(_aspect);
}

XMVECTOR Camera3D::GetPositionXM() const
{
    return XMLoadFloat3(&_position);
}

XMFLOAT3 Camera3D::GetPosition() const
{
    return _position;
}

XMVECTOR Camera3D::GetRightXM() const
{
    return XMLoadFloat3(&_right);
}

XMFLOAT3 Camera3D::GetRight() const
{
    return _right;
}

XMVECTOR Camera3D::GetUpXM() const
{
    return XMLoadFloat3(&_up);
}

XMFLOAT3 Camera3D::GetUp() const
{
    return _up;
}

XMVECTOR Camera3D::GetLookXM() const
{
    return XMLoadFloat3(&_look);
}

XMFLOAT3 Camera3D::GetLook() const
{
    return _look;
}

float Camera3D::GetNearZ() const
{
    return _nearZ;
}

float Camera3D::GetFarZ() const
{
    return _farZ;
}

float Camera3D::GetAspect() const
{
    return _aspect;
}

float Camera3D::GetFovY() const
{
    return _fovY;
}

float Camera3D::GetFovX() const
{
    auto nearWindowHeight = 2.0f * _nearZ * tanf(0.5f * _fovY);

    float halfWidth = 0.5f * nearWindowHeight;
    return 2.0f * atanf(halfWidth / _nearZ);
}

void graphics::Camera3D::GetCameraInfo(const data::CameraInfo& info)
{
    _position.x = info._position.x;
    _position.y = info._position.y;
    _position.z = info._position.z;

    _right.x = info._right.x;
    _right.y = info._right.y;
    _right.z = info._right.z;

    _up.x = info._up.x;
    _up.y = info._up.y;
    _up.z = info._up.z;

    _look.x = info._look.x;
    _look.y = info._look.y;
    _look.z = info._look.z;

    _nearZ = info._nearZ;
    _farZ  = info._farZ;
    _fovY  = info._fovY * math::constant::PI;

    _view._11 = info._view[0][0];
    _view._12 = info._view[0][1];
    _view._13 = info._view[0][2];
    _view._14 = info._view[0][3];

    _view._21 = info._view[1][0];
    _view._22 = info._view[1][1];
    _view._23 = info._view[1][2];
    _view._24 = info._view[1][3];

    _view._31 = info._view[2][0];
    _view._32 = info._view[2][1];
    _view._33 = info._view[2][2];
    _view._34 = info._view[2][3];

    _view._41 = info._view[3][0];
    _view._42 = info._view[3][1];
    _view._43 = info._view[3][2];
    _view._44 = info._view[3][3];
}

void graphics::Camera3D::SetLens(float aspect)
{
    SetLens(_fovY, aspect, _nearZ, _farZ);
}

void Camera3D::SetLens(float fovY, float aspect, float zn, float zf)
{
    _fovY   = fovY;
    _aspect = aspect;

    _nearZ = zn;
    _farZ  = zf;

    auto farWindowHeight = 2.0f * _farZ * tanf(0.5f * _fovY);

    XMMATRIX P = XMMatrixPerspectiveFovLH(_fovY, _aspect, _nearZ, _farZ);
    ;
    XMStoreFloat4x4(&_proj, P);
}

XMMATRIX Camera3D::View() const
{
    return XMLoadFloat4x4(&_view);
}

XMMATRIX Camera3D::Proj() const
{
    return XMLoadFloat4x4(&_proj);
}

XMMATRIX Camera3D::ViewProj() const
{
    return XMMatrixMultiply(View(), Proj());
}