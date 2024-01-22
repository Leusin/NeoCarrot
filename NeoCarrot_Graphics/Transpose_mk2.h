/// Transpose_mk2.h : ������ Transpos ������Ʈ�� CameraPtr �� ��ģ ������Ʈ
///
/// 2024-01-22

#pragma once

// ���
#include "IComponent.h"

#include <directxmath.h>

namespace graphics
{
// ���� ����
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

    // world, view, proj ���� ��ȯ
    DirectX::XMMATRIX GetWorldViewProj();

    void SetWorld(const DirectX::XMMATRIX& world);
    void SetView(const DirectX::XMMATRIX& view);
    void SetProj(const DirectX::XMMATRIX& proj);

    // world, view, proj �� �Ѳ����� �ʱ�ȭ
    void SetTM(const DirectX::XMMATRIX& world,
               const DirectX::XMMATRIX& view,
               const DirectX::XMMATRIX& proj);

private:
    void UpdateDataFormCamera();

private:
    // ��ȯ ����
    DirectX::XMFLOAT4X4 _world; // ���� ��ȯ ��� (����->����)
    DirectX::XMFLOAT4X4 _view;  // �þ� ��ȯ ��� (ī�޶� ��)
    DirectX::XMFLOAT4X4 _proj;  // ���� ��ȯ ��� (����/����)

    // ī�޶� ��ġ
    DirectX::XMFLOAT3 _eyePosW;

    // ī�޶� ������
    Camera3D* _camera;
};

} // namespace graphics