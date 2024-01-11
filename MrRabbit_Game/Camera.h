/// Camera.h : 엔티티가 컴포넌트로서 가질 수 있는 카메라.
/// directxmath 에 의존하지 않고 따로 만든 수학 라이브러리를 사용한다.
/// 
/// 주로 카메라이 이동을 제어한다.
///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "EntityEnum.h"
#include "CameraInfo.h"

#include <memory>

 namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;

namespace game
{

class Transform;

class Camera : public core::IComponent
{
public:
    Camera(EntityPtr entityPtr);
    ~Camera();

    void Update(float dt) override;

    // 카메라 이동
    void Strafe(float distance); // 횡이동
    void Walk(float distance);   // 축이동

    // 카메라 회전
    void Pitch(float angle);   // 위아래
    void RotateY(float angle); // 좌우

    /// 시야 행렬 구축

    // 매 프래임, 카메라 위치 또는 방향 수정 후
    // 이 메서들을 호출해 시야 행렬을 재구축한다.
    // void UpdateViewMatrix();

    data::CameraInfo GetCameraInfo();

private:

    Transform* _transform;

    data::CameraInfo _cameraInfo;

};

} // namespace game