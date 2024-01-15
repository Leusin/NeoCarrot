#pragma once
#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{
// ���� ����
template <typename V>
class VertexBuffer;
class IndexBuffer;
struct PosCol;

// ����
class GridScript : public core::IComponent, virtual core::GetEntity
{
public:
    GridScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    IndexBuffer*          _indexBuffer;
    VertexBuffer<PosCol>* _vertexBuffer;

    void SetVertexBuffer();
    void SetIndexBuffer();
};

}