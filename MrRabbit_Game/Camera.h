/// Camera.h : 엔티티가 컴포넌트로서 가질 수 있는 카메라.
/// directxmath 에 의존하지 않고 따로 만든 수학 라이브러리를 사용한다.
///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "Matrix.h"
#include "Vector3.h"

namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();

    /// 카메라 변환


    math::Vector3<float> GetPosition() const;
    void                 SetPosition(float x, float y, float z);
    void                 SetPosition(const math::Vector3<float>& pos);

    math::Vector3<float> GetRight() const;
    math::Vector3<float> GetUp() const;
    math::Vector3<float> GetLook() const;

    float GetAspect() const;
    float GetFovY() const;
    float GetFovX() const;

    float GetNearWindowWidth() const;
    float GetNearWindowHeight() const;
    float GetFarWindowWidth() const;
    float GetFarWindowHeight() const;

    /// 절두체 시야 제어

    void SetLens(float fovY, float aspect, float zn, float zf);

    // 카메라 공간 설정
    void LookAt(const math::Vector3<float>& pos, const math::Vector3<float>& target, const math::Vector3<float>& up);

    math::Matrix View() const;
    math::Matrix Proj() const;
    math::Matrix ViewProj() const;

    // 카메라 이동
    void Strafe(float distance); // 횡이동
    void Walk(float distance);   // 축이동

    // 카메라 회전
    void Pitch(float angle);   // 위아래
    void RotateY(float angle); // 좌우

    /// 시야 행렬 구축

    // 매프래임, 카메라 위치 또는 방향 수정 후
    // 이 메서들을 호출해 시야 행렬을 재구축한다.
    void UpdateViewMatrix();

private:
    // 월드 기준 카메라 좌표계
    // 원점
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f};
    // 기저
    math::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    math::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    math::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // 절두체 속성
    float _nearZ{000.1f};
    float _farZ{1000.f};
    float _aspect{1.0f};
    float _fovY{0.25f};
    float _nearWindowHeight;
    float _farWindowHeight;

    // 시야행렬 및 투영 행렬
    math::Matrix _view;
    math::Matrix _proj;
};

} // namespace game