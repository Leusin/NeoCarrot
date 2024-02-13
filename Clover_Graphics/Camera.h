/// Camera3D.h
///
/// 게임 엔진에서 카메라 컴포넌트가 보낸 카메라 정보를 받아 최종적으로 화면에 보이는 뷰 _proj 를 업데이트 한다.
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

    // 기저
    DirectX::XMFLOAT3 _right; // x
    DirectX::XMFLOAT3 _up;    // y
    DirectX::XMFLOAT3 _look;  // z
};
} // namespace graphics