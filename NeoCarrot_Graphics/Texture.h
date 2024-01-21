#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include "D3Devices.h"

#include <d3d11.h>
#include <wrl.h>
#include <directxmath.h>

namespace graphics
{

class Texture : public core::IComponent, virtual core::GetEntity
{
public:
    Texture(EntityPtr entityPtr, const std::wstring& filename);

    void Update(float dt);

    void SetEffect();

private:
    // ÅØ½ºÃÄ
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _diffuseMapSRV;
    DirectX::XMFLOAT4X4                              _texTransform;

    D3Devices* _d3device;
};

} // namespace graphics