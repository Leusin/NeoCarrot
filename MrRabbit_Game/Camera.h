/// Camera.h : ��ƼƼ�� ������Ʈ�μ� ���� �� �ִ� ī�޶�.
/// directxmath �� �������� �ʰ� ���� ���� ���� ���̺귯���� ����Ѵ�.
///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "Vector3.h"
#include "Matrix.h"

namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();

    /*
    DirectX::XMVECTOR GetPositionXM() const;
    DirectX::XMFLOAT3 GetPosition() const;
    void SetPosition(float x, float y, float z);
    void SetPosition(const DirectX::XMFLOAT3 &v);

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

    float GetNearWindowWidth() const;
    float GetNearWindowHeight() const;
    float GetFarWindowWidth() const;
    float GetFarWindowHeight() const;

    /// ����ü �þ� ����

    void SetLens(float fovY, float aspect, float zn, float zf);

    // ī�޶� ���� ����
    void LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp);
    void LookAt(const DirectX::XMFLOAT3 &pos, const DirectX::XMFLOAT3 &target, const DirectX::XMFLOAT3 &up);

    DirectX::XMMATRIX View() const;
    DirectX::XMMATRIX Proj() const;
    DirectX::XMMATRIX ViewProj() const;

    /// ī�޶� ��ȯ

    // ī�޶� �̵�
    void Strafe(float d); // Ⱦ�̵�
    void Walk(float d);   // ���̵�

    // ī�޶� ȸ��
    void Pitch(float angle);   // ���Ʒ�
    void RotateY(float angle); // �¿�

    /// �þ� ��� ����

    // ��������, ī�޶� ��ġ �Ǵ� ���� ���� ��
    // �� �޼����� ȣ���� �þ� ����� �籸���Ѵ�.
    void UpdateViewMatrix();
    */

private:
    // ���� ���� ī�޶� ��ǥ��
    // ����
    math::Vector3<float> _position{0.0f, 0.0f, 0.0f}; 
    // ����
    math::Vector3<float> _right{1.0f, 0.0f, 0.0f};    // x
    math::Vector3<float> _up{0.0f, 1.0f, 0.0f};       // y
    math::Vector3<float> _look{0.0f, 0.0f, 1.0f};     // z

    // ����ü �Ӽ�
    float _nearZ;
    float _farZ;
    float _aspect; // ��Ⱦ��
    float _fovY;   // y �þ߰�
    float _nearWindowHeight;
    float _farWindowHeight;

    // �þ���� �� ���� ���
    math::Matrix _view;
    math::Matrix _proj;
};

} // namespace game