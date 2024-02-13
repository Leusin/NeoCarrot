#include "D3D11Devices.h"

#include <cassert>

namespace graphics
{

Devices::Devices()
{
    CreateDeviceAndImmdiateContext();
    CreateDeferredContext();

    // 4XMSAA의품질수준 체크
    UINT l4xMsaaQality;
    _d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &l4xMsaaQality);
    assert(l4xMsaaQality > 0); // 환된 수준값이 0보다 크도록 강제
}

Devices::~Devices()
{
    _d3dDeferredContext->ClearState();
    _d3dDeferredContext->Flush();

    _d3dImmdiateContext->ClearState();
    _d3dImmdiateContext->Flush();
}

ID3D11Device* Devices::Device() const
{
    return _d3dDevice.Get();
}

ID3D11DeviceContext* Devices::ImmediateContext() const
{
    return _d3dImmdiateContext.Get();
}

ID3D11DeviceContext* Devices::DeferredContext() const
{
    return _d3dDeferredContext.Get();
}

void Devices::CreateDeviceAndImmdiateContext()
{
    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE d3dDriverType{D3D_DRIVER_TYPE_HARDWARE};

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT           hr = D3D11CreateDevice(nullptr,
                                   d3dDriverType,
                                   nullptr,
                                   createDeviceFlags,
                                   nullptr,
                                   0,
                                   D3D11_SDK_VERSION,
                                   _d3dDevice.GetAddressOf(),
                                   &featureLevel,
                                   _d3dImmdiateContext.GetAddressOf());

    if (FAILED(hr))
    {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return;
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
        return;
    }
}

void Devices::CreateDeferredContext()
{
    _d3dDevice->CreateDeferredContext(0, _d3dDeferredContext.GetAddressOf());

    assert(_d3dDeferredContext && "Deferred Context 가 생성되지 않음");
}

} // namespace graphics