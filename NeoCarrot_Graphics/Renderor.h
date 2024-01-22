#pragma once

#include "D3Devices.h"
#include "GetEntity.h"
#include "IComponent.h"


namespace graphics
{

class Renderor: public core::IComponent, virtual core::GetEntity
{
public:
    Renderor(EntityPtr entityPtr, D3D_PRIMITIVE_TOPOLOGY primitiveTopology);

    void Update(float dt) override;

    // 혹시라도 중간에 그리는 방식을 중간에 바꾼다면
    void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology);

private:
    void UpdateRender();

private:
    D3Devices* _d3devices;
    D3D_PRIMITIVE_TOPOLOGY _primitiveTopology;
};

} // namespace graphics