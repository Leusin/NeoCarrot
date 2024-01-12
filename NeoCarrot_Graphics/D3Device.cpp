#include "D3Device.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
D3Device::D3Device(ID3D11Device* device, ID3D11DeviceContext* dContext) 
    : _d3dDevice(device)
    , _d3dImmediateContext(dContext)
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd D3Device Component\n";
#endif // _DEBUG
}

void D3Device::Awake()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\t\tAdd VertexBuffer D3Device Awake\n";
#endif // _DEBUG;
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
