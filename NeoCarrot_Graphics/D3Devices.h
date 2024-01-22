#pragma once

#include "IComponent.h"

#include <d3d11.h>

namespace graphics
{
// ���� ����
class D3D11Context_mk2;

// ����
class D3Devices : public core::IComponent
{
public:
    D3Devices(const D3D11Context_mk2* d3d11context);

    void Awake() override;
    void Update(float dt) override;

    ID3D11Device*        GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

    // ����̽�
    ID3D11Device* _d3dDevice;
    // ����̽� ���ؽ�Ʈ
    ID3D11DeviceContext* _d3dImmediateContext;
    // ���� ����
    ID3D11RasterizerState* _rasterizerState;


    void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology);

private:
    void RasterizerStateSetRanderstate();
};

} // namespace graphics