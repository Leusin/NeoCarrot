#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
// 전방 선언
template <typename V>
class VertexBuffer;
class IndexBuffer;
struct Col;

// 본문
class AxisScript : public core::IComponent, virtual core::GetEntity
{
public:
    AxisScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    IndexBuffer*          _indexBuffer;
    VertexBuffer<Col>* _vertexBuffer;
};

} // namespace graphics