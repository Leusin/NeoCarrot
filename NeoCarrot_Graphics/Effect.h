#pragma once

#include "D3Device.h"
#include "Entity.h"
#include "EntityEnum.h"
#include "IComponent.h"

#include <d3dx11effect.h>
#include <wrl.h>
#include <string>

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
class D3Device;

class Effect : public core::IComponent
{

public:
    Effect(EntityPtr entityPtr, std::wstring fileName);

    void Awake() override;

     // ¿Ã∆Â∆Æ
    Microsoft::WRL::ComPtr<ID3DX11Effect>               _fx{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectTechnique>      _tech{nullptr};
    Microsoft::WRL::ComPtr<ID3DX11EffectMatrixVariable> _fxWorldViewProj{nullptr};

private:
    EntityWeakPtr _entity;
    D3Device*     _d3device;

    std::wstring _fileName;
};

} // namespace graphics