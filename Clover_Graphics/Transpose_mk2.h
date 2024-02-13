/// Transpose_mk2.h : 기존의 Transpos 컴포넌트와 CameraPtr 를 합친 컴포넌트
///
/// 2024-01-22

#pragma once

// 헤더
#include "IComponent.h"

#include <directxmath.h>

namespace graphics
{
// 전방 선언
class Camera3D;

class Transpose_mk2: public core::IComponent
{

public:
    Transpose_mk2(Camera3D* camera);

    void Update(float dt) override;

public:
    DirectX::XMMATRIX GetWorld();
    DirectX::XMMATRIX GetView();
    DirectX::XMMATRIX GetProj();

    // world, view, proj 곱을 반환
    DirectX::XMMATRIX GetWorldViewProj();

    void SetWorld(const DirectX::XMMATRIX& world);
    void SetView(const DirectX::XMMATRIX& view);
    void SetProj(const DirectX::XMMATRIX& proj);

    // world, view, proj 를 한꺼번에 초기화
    void SetTM(const DirectX::XMMATRIX& world,
               const DirectX::XMMATRIX& view,
               const DirectX::XMMATRIX& proj);

private:
    void UpdateDataFormCamera();

private:
    // 변환 관련
    DirectX::XMFLOAT4X4 _world; // 월드 변환 행렬 (로컬->월드)
    DirectX::XMFLOAT4X4 _view;  // 시야 변환 행렬 (카메라 뷰)
    DirectX::XMFLOAT4X4 _proj;  // 투영 변환 행렬 (원근/직교)

    // 카메라 위치
    DirectX::XMFLOAT3 _eyePosW;

    // 카메라 포인터
    Camera3D* _camera;
};

} // namespace graphics