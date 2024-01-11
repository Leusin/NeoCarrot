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

class Camera3D
{
public:
    Camera3D();
    Camera3D(int clientWidth, int clientHeight);
    ~Camera3D();

    void Initialize();

    //
    // 인터페이스 함수
    //

    DirectX::XMVECTOR GetPositionXM() const;
    DirectX::XMFLOAT3 GetPosition() const;

    DirectX::XMVECTOR GetRightXM() const;
    DirectX::XMFLOAT3 GetRight() const;
    DirectX::XMVECTOR GetUpXM() const;
    DirectX::XMFLOAT3 GetUp() const;
    DirectX::XMVECTOR GetLookXM() const;
    DirectX::XMFLOAT3 GetLook() const;

    float GetNearZ() const;
    float GetFarZ() const;
    float GetAspect() const;
    float GetFovY() const;
    float GetFovX() const;

    void GetCameraInfo(const data::CameraInfo& info);

    /// 절두체 시야 제어
    void SetLens(float aspect);

    DirectX::XMMATRIX View() const;
    DirectX::XMMATRIX Proj() const;
    DirectX::XMMATRIX ViewProj() const;

private:
    void SetLens(float fovY, float aspect, float zn, float zf);

    // 월드 기준 카메라 좌표계
    // 원점
    DirectX::XMFLOAT3 _position;
    // 기저
    DirectX::XMFLOAT3 _right; // x
    DirectX::XMFLOAT3 _up;    // y
    DirectX::XMFLOAT3 _look;  // z

    // 절두체 속성
    float _nearZ;
    float _farZ;
    float _aspect; // 종횡비
    float _fovY;   // y 시야각

    // 시야행렬 및 투영 행렬
    DirectX::XMFLOAT4X4 _view;
    DirectX::XMFLOAT4X4 _proj;
};
} // namespace grahics