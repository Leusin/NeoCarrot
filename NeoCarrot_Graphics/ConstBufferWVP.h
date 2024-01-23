#pragma once

#include "ConstantBuffer.h"

namespace graphics
{
struct ContWorldViewProj;

class ConstBufferWVP: public ConstantBuffer<ContWorldViewProj>
{
public:
    ConstBufferWVP(EntityPtr entityPtr);

    void Awake();
    void Update(float dt) override;

private:
    void UpdateVariable();
};

} // namespace graphics