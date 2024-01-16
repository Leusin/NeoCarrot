#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

#include <vector>
#include <windows.h>

namespace loader{ class FbxLoader; }

namespace graphics
{
// 전방 선언
class D3Devices;
template <typename V>
class VertexBuffer;
struct PosNormal;
class IndexBuffer;
class Effect;

// 본문
class BoxScript : public core::IComponent, virtual core::GetEntity
{
public:
    BoxScript(EntityPtr entityPtr, loader::FbxLoader* fbxLoader);

    void Awake() override;
    void Update(float dt) override;

private:

    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);
    void SetBuffersToContext(UINT& offset);
    void DrawIndexed(const int& idx);

    D3Devices*               _devices;
    IndexBuffer*             _indexBuffer;
    VertexBuffer<PosNormal>* _vertexBuffer;
    Effect*                  _effect;
};

} // namespace graphics