/// Camera3D.h
///
/// ���� �������� ī�޶� ������Ʈ�� ���� ī�޶� ������ �޾� ���������� ȭ�鿡 ���̴� �� _proj �� ������Ʈ �Ѵ�.
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
    // �������̽� �Լ�
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

    /// ����ü �þ� ����
    void SetLens(float aspect);

    DirectX::XMMATRIX View() const;
    DirectX::XMMATRIX Proj() const;
    DirectX::XMMATRIX ViewProj() const;

private:
    void SetLens(float fovY, float aspect, float zn, float zf);

    // ���� ���� ī�޶� ��ǥ��
    // ����
    DirectX::XMFLOAT3 _position;
    // ����
    DirectX::XMFLOAT3 _right; // x
    DirectX::XMFLOAT3 _up;    // y
    DirectX::XMFLOAT3 _look;  // z

    // ����ü �Ӽ�
    float _nearZ;
    float _farZ;
    float _aspect; // ��Ⱦ��
    float _fovY;   // y �þ߰�

    // �þ���� �� ���� ���
    DirectX::XMFLOAT4X4 _view;
    DirectX::XMFLOAT4X4 _proj;
};
} // namespace grahics