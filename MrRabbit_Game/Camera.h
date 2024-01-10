/// Camera.h : 엔티티가 컴포넌트로서 가질 수 있는 카메라.
/// directxmath 에 의존하지 않고 따로 만든 수학 라이브러리를 사용한다.
///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "CameraInfo.h"

#include "Matrix.h"
#include "Vector3.h"

#include "EntityEnum.h"

#include <memory>

 namespace core
{
template <typename T, typename U>
class Entity;
}

using EntityPtr     = std::shared_ptr<core::Entity<game::Tag, game::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<game::Tag, game::Layer>>;

namespace game
{

class Transform;

class Camera : public core::IComponent
{
public:
    Camera(EntityPtr entityPtr);
    ~Camera();

    void Update(float dt) override;

    /// 카메라 변환

    //float GetAspect() const;
    float GetFovY() const;
    float GetFovX() const;

    float GetNear() const;
    float GetFar() const;

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

    // 매 프래임, 카메라 위치 또는 방향 수정 후
    // 이 메서들을 호출해 시야 행렬을 재구축한다.
    //void UpdateViewMatrix();

private:

    Transform* _transform;

    CameraInfo _cInfo;

};

} // namespace game