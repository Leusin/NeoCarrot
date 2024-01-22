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

    // Ȥ�ö� �߰��� �׸��� ����� �߰��� �ٲ۴ٸ�
    void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology);

private:
    void UpdateRender();

private:
    D3Devices* _d3devices;
    D3D_PRIMITIVE_TOPOLOGY _primitiveTopology;
};

} // namespace graphics