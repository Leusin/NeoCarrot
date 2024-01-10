#include "Camera3D.h"
#include "Constants.h"

using namespace DirectX;
using namespace grahics;

Camera3D::Camera3D()
{
    SetLens(0.25f, 1.0f, 000.1f, 1000.f);
}

Camera3D::~Camera3D()
{
}

XMVECTOR Camera3D::GetPositionXM() const
{
    return XMLoadFloat3(&_position);
}

XMFLOAT3 Camera3D::GetPosition() const
{
    return _position;
}

void Camera3D::SetPosition(float x, float y, float z)
{
    _position = XMFLOAT3(x, y, z);
}

void Camera3D::SetPosition(const XMFLOAT3 &v)
{
    _position = v;
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
    float halfWidth = 0.5f * GetNearWindowHeight();
    return 2.0f * atanf(halfWidth / _nearZ);
}

float Camera3D::GetNearWindowWidth() const
{
    return _aspect * _nearWindowHeight;
}

float Camera3D::GetNearWindowHeight() const
{
    return _nearWindowHeight;
}

float Camera3D::GetFarWindowWidth() const
{
    return _aspect * _farWindowHeight;
}

float Camera3D::GetFarWindowHeight() const
{
    return _farWindowHeight;
}

void Camera3D::SetLens(float fovY, float aspect, float zn, float zf)
{
    _fovY = fovY * math::constant::PI;
    _aspect = aspect;

    _nearZ = zn;
    _farZ = zf;

    _nearWindowHeight = 2.0f * _nearZ * tanf(0.5f * _fovY);
    _farWindowHeight = 2.0f * _farZ * tanf(0.5f * _fovY);

    XMMATRIX P = XMMatrixPerspectiveFovLH(_fovY, _aspect, _nearZ, _farZ);
    XMStoreFloat4x4(&_proj, P);
}

void Camera3D::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
    XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
    XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
    XMVECTOR U = XMVector3Cross(L, R);

    XMStoreFloat3(&_position, pos);
    XMStoreFloat3(&_look, L);
    XMStoreFloat3(&_right, R);
    XMStoreFloat3(&_up, U);
}

void Camera3D::LookAt(const XMFLOAT3 &pos, const XMFLOAT3 &target, const XMFLOAT3 &up)
{
    XMVECTOR P = XMLoadFloat3(&pos);
    XMVECTOR T = XMLoadFloat3(&target);
    XMVECTOR U = XMLoadFloat3(&up);

    LookAt(P, T, U);
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

void Camera3D::Strafe(float d)
{
    //_position += d * _look
    XMVECTOR s = XMVectorReplicate(d);
    XMVECTOR r = XMLoadFloat3(&_right);
    XMVECTOR p = XMLoadFloat3(&_position);
    XMStoreFloat3(&_position, XMVectorMultiplyAdd(s, r, p));
}

void Camera3D::Walk(float d)
{
    //_position += d * _right
    XMVECTOR s = XMVectorReplicate(d);
    XMVECTOR l = XMLoadFloat3(&_look);
    XMVECTOR p = XMLoadFloat3(&_position);
    XMStoreFloat3(&_position, XMVectorMultiplyAdd(s, l, p));
}

void Camera3D::Pitch(float angle)
{
    // 상향 벡터(y)와 시선 벡터(z) 를 오른쪽 벡터(x)애 대해 회전한다

    XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);

    XMStoreFloat3(&_up, XMVector3TransformNormal(XMLoadFloat3(&_up), R));
    XMStoreFloat3(&_look, XMVector3TransformNormal(XMLoadFloat3(&_look), R));
}

void Camera3D::RotateY(float angle)
{
    // 기저 벡터를 월드 y 축에 대해 회전한다

    XMMATRIX R = XMMatrixRotationY(angle);

    XMStoreFloat3(&_right, XMVector3TransformNormal(XMLoadFloat3(&_right), R));
    XMStoreFloat3(&_up, XMVector3TransformNormal(XMLoadFloat3(&_up), R));
    XMStoreFloat3(&_look, XMVector3TransformNormal(XMLoadFloat3(&_look), R));
}

void Camera3D::UpdateViewMatrix()
{
    XMVECTOR R = XMLoadFloat3(&_right);
    XMVECTOR U = XMLoadFloat3(&_up);
    XMVECTOR L = XMLoadFloat3(&_look);
    XMVECTOR P = XMLoadFloat3(&_position);

    //
    // 오른쪽, 상향, 시선 벡터 정규직교화
    //

    L = XMVector3Normalize(L);
    U = XMVector3Normalize(XMVector3Cross(L, R));
    R = XMVector3Cross(U, L);

    //
    // 시야 행렬을 채운다
    //

    float x = -XMVectorGetX(XMVector3Dot(P, R));
    float y = -XMVectorGetX(XMVector3Dot(P, U));
    float z = -XMVectorGetX(XMVector3Dot(P, L));

    XMStoreFloat3(&_right, R);
    XMStoreFloat3(&_up, U);
    XMStoreFloat3(&_look, L);

    _view(0, 0) = _right.x;
    _view(1, 0) = _right.y;
    _view(2, 0) = _right.z;
    _view(3, 0) = x;

    _view(0, 1) = _up.x;
    _view(1, 1) = _up.y;
    _view(2, 1) = _up.z;
    _view(3, 1) = y;

    _view(0, 2) = _look.x;
    _view(1, 2) = _look.y;
    _view(2, 2) = _look.z;
    _view(3, 2) = z;

    _view(0, 3) = 0.0f;
    _view(1, 3) = 0.0f;
    _view(2, 3) = 0.0f;
    _view(3, 3) = 1.0f;
}
