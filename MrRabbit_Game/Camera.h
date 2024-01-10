/// Camera.h : ��ƼƼ�� ������Ʈ�μ� ���� �� �ִ� ī�޶�.
/// directxmath �� �������� �ʰ� ���� ���� ���� ���̺귯���� ����Ѵ�.
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

    /// ī�޶� ��ȯ


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

    // ��������, ī�޶� ��ġ �Ǵ� ���� ���� ��
    // �� �޼����� ȣ���� �þ� ����� �籸���Ѵ�.
    void UpdateViewMatrix();

private:
    // ���� ���� ī�޶� ��ǥ��
    // ����
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f};
    // ����
    math::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    math::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    math::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // ����ü �Ӽ�
    float _nearZ{000.1f};
    float _farZ{1000.f};
    float _aspect{1.0f};
    float _fovY{0.25f};
    float _nearWindowHeight;
    float _farWindowHeight;

    // �þ���� �� ���� ���
    math::Matrix _view;
    math::Matrix _proj;
};

} // namespace game