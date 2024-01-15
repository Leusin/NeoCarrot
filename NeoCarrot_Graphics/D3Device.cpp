#include "D3Device.h"

#include "D3D11Context_mk2.h"
#include "Devices.h"
#include "RenderStates.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
D3Device::D3Device(const D3D11Context_mk2* d3d11context) 
    : _d3dDevice(d3d11context->GetDevices()->Device())
    , _d3dImmediateContext(d3d11context->GetDevices()->ImmediateContext()),
    _rasterizerState(d3d11context->GetRenderStates()->solidRS.Get())
{
    assert(_d3dDevice && _d3dImmediateContext);
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd D3Device Component\n";
#endif // _DEBUG
}

void D3Device::Awake()
{
}

void D3Device::Update(float dt)
{
}

ID3D11Device* D3Device::GetDevice()
{
    return _d3dDevice;
}
ID3D11DeviceContext* D3Device::GetDeviceContext()
{
    return _d3dImmediateContext;
}
} // namespace graphics
