#include "D3Device.h"

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
D3Device::D3Device(ID3D11Device* device, ID3D11DeviceContext* dContext, ID3D11RasterizerState* rasterizerState) 
    : _d3dDevice(device)
    , _d3dImmediateContext(dContext),
    _rasterizerState(rasterizerState)
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
