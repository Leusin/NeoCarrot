/// Camera3D.h
///
/// ���� �������� ī�޶� ������Ʈ�� ���� ī�޶� ������ �޾� ���������� ȭ�鿡 ���̴� �� _proj �� ������Ʈ �Ѵ�.
///
/// 2024-01-04


#pragma once

#include <directxmath.h>

namespace data
{
struct CameraInfo;
}

namespace graphics
{

class Camera
{
public:
    Camera();
    Camera(const Camera&);
    ~Camera();

    void Render();

    DirectX::XMFLOAT3 GetPosition();
    DirectX::XMFLOAT3 GetRotation();
    DirectX::XMMATRIX GetViewMatrix();

    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetViewMatirx(DirectX::XMMATRIX& view);

private:
    DirectX::XMFLOAT3 _position;
    DirectX::XMFLOAT3 _rotation;
    DirectX::XMFLOAT4X4 _view;

    // ����
    DirectX::XMFLOAT3 _right; // x
    DirectX::XMFLOAT3 _up;    // y
    DirectX::XMFLOAT3 _look;  // z
};
} // namespace graphics