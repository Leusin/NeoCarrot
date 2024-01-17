#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"
#include "StructedBuffer.h"

#include <vector>
#include <d3d11.h>
#include <windows.h>
#include <d3dx11effect.h>

namespace loader{ class FbxLoader; }

namespace graphics
{
// 전방 선언
template <typename V>
class VertexBuffer;
class D3Devices;
class IndexBuffer;
class Effect;
struct PosNormal;

// 본문
class BoxScript : public core::IComponent, virtual core::GetEntity
{
public:
    BoxScript(EntityPtr entityPtr, loader::FbxLoader* fbxLoader);

    void Awake() override;
    void Update(float dt) override;

private:
    void SetBuffers(model::Mesh& data);
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);
    void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology);
    void SetBuffersToContext(UINT& offset);
    void RenderWithEffectPasses(const D3DX11_TECHNIQUE_DESC& techDesc, UINT& offset); 
    void DrawIndexed(const int& idx);

    D3Devices*               _devices;
    IndexBuffer*             _indexBuffer;
    VertexBuffer<PosNormal>* _vertexBuffer;
    Effect*                  _effect;
};

} // namespace graphics