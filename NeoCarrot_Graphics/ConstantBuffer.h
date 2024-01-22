/// ConstantBuffer.h
/// 상수 버퍼는 n개 늘어날 수 있다고 생각하기 때문에 분리하였다.
///
/// 2024-01-22


#pragma once

#include "D3Devices.h"
#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <wrl.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

template<typename CB>
class ConstantBuffer: public core::IComponent, virtual core::GetEntity
{
public:
    ConstantBuffer(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    D3Devices* _d3devices{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer{ nullptr };

private:
    void CreateConstantBuffer();

    // 렌더 전에 사용자가 변수를 업데이트 해야 한다.
    void SetConstantBuffer();
};

//////////////////////////////////////////////////////////////////////
template<typename CB>
inline ConstantBuffer<CB>::ConstantBuffer(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
{
    static_assert(std::is_class<CB>::value &&
                  "ConstantBuffer 의 템플릿 매개변수는 구조체(혹은 적어도 "
                  "클래스)");
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd ConstantBuffer Component\n";
#endif // _DEBUG;
}

//////////////////////////////////////////////////////////////////////
template<typename CB>
inline void ConstantBuffer<CB>::Awake()
{
    CreateConstantBuffer();
}

template<typename CB>
inline void ConstantBuffer<CB>::Update(float dt)
{
    // 보통 Update variables 가 선행된다.
    SetConstantBuffer();
}

//////////////////////////////////////////////////////////////////////
template<typename CB>
inline void ConstantBuffer<CB>::CreateConstantBuffer()
{
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(CB);
    bd.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags    = 0;
    device->CreateBuffer(&bd, nullptr, _constantBuffer.GetAddressOf());
}

template<typename CB>
inline void ConstantBuffer<CB>::SetConstantBuffer()
{
    auto deviceContext = _d3devices->GetDeviceContext();
    deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
}

} // namespace graphics