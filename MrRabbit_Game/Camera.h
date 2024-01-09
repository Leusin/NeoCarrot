/// Camera.h : ��ƼƼ�� ������Ʈ�μ� ���� �� �ִ� ī�޶�.
/// directxmath �� �������� �ʰ� ���� ���� ���� ���̺귯���� ����Ѵ�.
///
/// 2024-01-09

#pragma once

#include "../UnityLike_Core/IComponent.h"
#include "../Bunny_Math/Vector3.h"

namespace game
{

class Camera : public core::IComponent
{
public:
    Camera();
    ~Camera();

private:
    // ���� ���� ī�޶� ��ǥ��
    // ����
    me::Vector3<float> _position{0.0f, 0.0f, 0.0f};
    // ����
    me::Vector3<float> _right{1.0f, 0.0f, 0.0f}; // x
    me::Vector3<float> _up{0.0f, 1.0f, 0.0f};    // y
    me::Vector3<float> _look{0.0f, 0.0f, 1.0f};  // z

    // ����ü �Ӽ�
    float _nearZ;
    float _farZ;
    float _aspect; // ��Ⱦ��
    float _fovY;   // y �þ߰�
    float _nearWindowHeight;
    float _farWindowHeight;

    /// TODO 
    ///   4x4 ����� ���� ��
    ///   �Ʒ� �ɹ� �߰�
    // �þ���� �� ���� ���
    // DirectX::XMFLOAT4X4 _view;
    // DirectX::XMFLOAT4X4 _proj;
};

} // namespace game