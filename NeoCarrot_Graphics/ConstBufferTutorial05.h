#pragma once

#include "ConstantBuffer.h"

namespace graphics
{
struct ConstBuffWorldViewProj;

class ConstBufferTutorial05: public ConstantBuffer<ConstBuffWorldViewProj>
{
public:
    ConstBufferTutorial05(EntityPtr entityPtr);

    void Awake();
    void Update(float dt) override;

private:
    void UpdateVariable();
};

} // namespace graphics