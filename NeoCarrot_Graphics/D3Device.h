#pragma once

#include "IComponent.h"

#include <d3d11.h>

namespace graphics
{

class D3Device : public core::IComponent
{
public:
    D3Device(ID3D11Device* _device, ID3D11DeviceContext* _dContext);

    void Awake() override;

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

private:
    // 디바이스
    ID3D11Device* _d3dDevice;

    // 디바이스 컨텍스트
    ID3D11DeviceContext* _d3dImmediateContext;
};

} // namespace graphics