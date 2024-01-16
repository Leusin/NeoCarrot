#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <memory>
#include <wrl.h>

namespace graphics
{
class D3Devices;
class Effect;

class InputLayout : public core::IComponent, virtual core::GetEntity
{
public:
    InputLayout(EntityPtr entityPtr, const D3D11_INPUT_ELEMENT_DESC* vertexDesc);

    void Awake() override;
    void Update(float dt) override;

    Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout{nullptr};

    void SetInputLayout();

private:
    D3Devices* _d3device{nullptr};
    Effect*   _effect{nullptr};

    const D3D11_INPUT_ELEMENT_DESC* _vertexDesc;
};
} // namespace graphics