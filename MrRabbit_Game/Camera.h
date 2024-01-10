/// Camera.h : ��ƼƼ�� ������Ʈ�μ� ���� �� �ִ� ī�޶�.
/// directxmath �� �������� �ʰ� ���� ���� ���� ���̺귯���� ����Ѵ�.
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

    /// ī�޶� ��ȯ

    //float GetAspect() const;
    float GetFovY() const;
    float GetFovX() const;

    float GetNear() const;
    float GetFar() const;

    /// ����ü �þ� ����

    void SetLens(float fovY, float aspect, float zn, float zf);

    // ī�޶� ���� ����
    void LookAt(const math::Vector3<float>& pos, const math::Vector3<float>& target, const math::Vector3<float>& up);

    math::Matrix View() const;
    math::Matrix Proj() const;
    math::Matrix ViewProj() const;

    // ī�޶� �̵�
    void Strafe(float distance); // Ⱦ�̵�
    void Walk(float distance);   // ���̵�

    // ī�޶� ȸ��
    void Pitch(float angle);   // ���Ʒ�
    void RotateY(float angle); // �¿�

    /// �þ� ��� ����

    // �� ������, ī�޶� ��ġ �Ǵ� ���� ���� ��
    // �� �޼����� ȣ���� �þ� ����� �籸���Ѵ�.
    //void UpdateViewMatrix();

private:

    Transform* _transform;

    CameraInfo _cInfo;

};

} // namespace game