#pragma once

#include "CompileShader.h"
#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{

class IndexBuffer_mk2: public core::IComponent, virtual core::GetEntity, public CompileShader
{
public:
    IndexBuffer_mk2(EntityPtr entityPtr, const std::wstring shaderFile);

    void Awake() override;
    void Update(float dt) override;

private:
    D3Devices* _d3devices{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
};

} // namespace graphics