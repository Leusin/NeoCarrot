#pragma once

#include "Entity.h"
#include "EntityEnum.h"
#include "IComponent.h"

#include <d3d11.h>
#include <wrl.h>
#include <memory>

using EntityPtr     = std::shared_ptr<core::Entity<core::Tag, core::Layer>>;
using EntityWeakPtr = std::weak_ptr<core::Entity<core::Tag, core::Layer>>;

namespace graphics
{
class D3Device;
class Effect;

class VertexLayout : public core::IComponent
{
public:
    VertexLayout(EntityPtr entityPtr, const D3D11_INPUT_ELEMENT_DESC* vertexDesc);

    void Awake() override;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout{nullptr};

private:
    EntityWeakPtr _entity;
    D3Device*     _d3device;
    Effect*       _effect;

    const D3D11_INPUT_ELEMENT_DESC* _vertexDesc;

};
} // namespace graphics