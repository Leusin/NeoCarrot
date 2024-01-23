#pragma once

#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{
// 전방 선언
template <typename V>
class VertexBuffer;
class IndexBuffer;
struct Col;

// 본문
class GridScript : public core::IComponent, virtual core::GetEntity
{
public:
    GridScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    IndexBuffer*          _indexBuffer;
    VertexBuffer<Col>* _vertexBuffer;

    void SetVertexBuffer();
    void SetIndexBuffer();
};

}