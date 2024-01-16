#include "D3Devices.h"

#include "D3D11Context_mk2.h"
#include "Devices.h"
#include "RenderStates.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
D3Devices::D3Devices(const D3D11Context_mk2* d3d11context) 
    : _d3dDevice(d3d11context->GetDevices()->Device())
    , _d3dImmediateContext(d3d11context->GetDevices()->ImmediateContext()),
    _rasterizerState(d3d11context->GetRenderStates()->solidRS.Get())
{
    assert(_d3dDevice && _d3dImmediateContext);
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd D3Device Component\n";
#endif // _DEBUG
}

void D3Devices::Awake()
{
}

void D3Devices::Update(float dt)
{
    RasterizerStateSetRanderstate();
}

ID3D11Device* D3Devices::GetDevice()
{
    return _d3dDevice;
}
ID3D11DeviceContext* D3Devices::GetDeviceContext()
{
    return _d3dImmediateContext;
}

void D3Devices::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology)
{
    _d3dImmediateContext->IASetPrimitiveTopology(primitiveTopology);
}

void D3Devices::RasterizerStateSetRanderstate()
{
    _d3dImmediateContext->RSSetState(_rasterizerState);
}
} // namespace graphics
