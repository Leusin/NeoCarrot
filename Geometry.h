#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"
#include "StructedBuffer.h"

#include <d3d11.h>
#include <d3dx11effect.h>
#include <vector>
#include <windows.h>

namespace loader
{
class FbxLoader;
}

namespace graphics
{
// º»¹®
class Geometry : public core::IComponent, virtual core::GetEntity
{
public:
    void Awake() override;
    void Update(float dt) override;

private:
    void SetBuffers(model::Mesh& data);
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);

    //D3Devices*               _devices;
    //IndexBuffer*             _indexBuffer;
    //VertexBuffer<PosNormal>* _vertexBuffer;
};

} // namespace graphics