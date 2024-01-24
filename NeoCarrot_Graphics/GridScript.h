#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "VertexBufferStruct.h"

namespace graphics
{
// 전방 선언
template <typename V>
class VertexBuffer;
class IndexBuffer;

// 본문
class GridScript : public core::IComponent, virtual core::GetEntity
{
private:
    struct PosCol : public Pos, public Col
    {
    };

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