#include "Camera.h"

namespace graphics
{

Camera::Camera()
    : _position{ 0.f, 0.f, 0.f }
    , _rotation{ 0.f, 0.f, 0.f }
    , _right{ 1.0f, 0.0f, 0.0f } // x
    , _up{ 0.0f, 1.0f, 0.0f }    // y
    , _look{ 0.0f, 0.0f, 1.0f }  // z
{
}

Camera::Camera(const Camera&)
{
}

Camera::~Camera()
{
}

void Camera::Render()
{
    DirectX::XMVECTOR upVector{ 0.f, 1.f, 0.f, 0.f };
    DirectX::XMVECTOR positionVector{ _position.x, _position.y, _position.z, 0.f };
    DirectX::XMVECTOR lookAtVector{ 0.f, 0.f, 1.f, 0.f };

    // 회전값을 라디안 단위로
    float pitch{ _rotation.x * 0.0174532925f };
    float yaw{ _rotation.y * 0.0174532925f };
    float roll{ _rotation.z * 0.0174532925f };
    
    DirectX::XMMATRIX rotationMatrix{ DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) };

    lookAtVector = DirectX::XMVectorAdd(positionVector, lookAtVector);

    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
    
    SetViewMatirx(view);
}

DirectX::XMFLOAT3 Camera::GetPosition()
{
    return _position;
}

DirectX::XMFLOAT3 Camera::GetRotation()
{
    return _rotation;
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
    return DirectX::XMLoadFloat4x4(&_view);
}

void Camera::SetPosition(float x, float y, float z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}

void Camera::SetRotation(float x, float y, float z)
{
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;
}

void Camera::SetViewMatirx(DirectX::XMMATRIX& view)
{
    XMStoreFloat4x4(&_view, view);
}

} // namespace graphics
