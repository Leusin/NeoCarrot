#pragma once

#include "ConstantBuffer.h"
#include "InputLayouts.h"

#include <directxmath.h>

namespace graphics
{
class ConstBufferTutorial06: public ConstantBuffer<ConstBuffLit>
{
public:
    ConstBufferTutorial06(EntityPtr entityPtr);

    void Awake();
    void Update(float dt) override;

private:
    void InitializeVariable();

    void RotateAnimation();
    void UpdateVariable();
    void RenderLight();

    std::vector<DirectX::XMFLOAT4> vLightDirs;
    std::vector<DirectX::XMFLOAT4> vLightColors;

    ConstBuffLit _cb;
};

} // namespace graphics