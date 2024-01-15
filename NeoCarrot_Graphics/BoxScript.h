#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

#include <vector>

namespace loader{ class FbxLoader; }

namespace graphics
{
// 전방 선언
template <typename V>
class VertexBuffer;
class IndexBuffer;
struct PosNormal;

// 본문
class BoxScript : public core::IComponent, virtual core::GetEntity
{
public:
    BoxScript(EntityPtr entityPtr, loader::FbxLoader* fbxLoader);

    void Awake() override;
    void Update(float dt) override;

private:
    IndexBuffer*          _indexBuffer;
    VertexBuffer<PosNormal>* _vertexBuffer;

    void SetVertexBuffer(std::vector<model::Mesh>& data);
    void SetIndexBuffer(std::vector<model::Mesh>& data);
};

}