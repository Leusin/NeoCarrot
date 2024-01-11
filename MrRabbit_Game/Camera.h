/// Camera.h : ��ƼƼ�� ������Ʈ�μ� ���� �� �ִ� ī�޶�.
/// directxmath �� �������� �ʰ� ���� ���� ���� ���̺귯���� ����Ѵ�.
/// 
/// �ַ� ī�޶��� �̵��� �����Ѵ�.
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

    // ī�޶� �̵�
    void Strafe(float distance); // Ⱦ�̵�
    void Walk(float distance);   // ���̵�

    // ī�޶� ȸ��
    void Pitch(float angle);   // ���Ʒ�
    void RotateY(float angle); // �¿�

    /// �þ� ��� ����

    // �� ������, ī�޶� ��ġ �Ǵ� ���� ���� ��
    // �� �޼����� ȣ���� �þ� ����� �籸���Ѵ�.
    // void UpdateViewMatrix();

    data::CameraInfo GetCameraInfo();

private:

    Transform* _transform;

    data::CameraInfo _cameraInfo;

};

} // namespace game