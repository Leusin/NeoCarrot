#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"
#include "InputLayouts.h"

namespace loader{class FbxLoader;}
namespace model{struct Mesh;}

namespace graphics
{
// 전방 선언
class D3Devices;
class IndexBuffer_mk2;
template<typename V>
class VertexResource;

class FbxLoad: public core::IComponent, virtual core::GetEntity
{
public:
    FbxLoad(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file);

public:
    void Awake() override;

private:
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);

    void PushBackPosition(const model::Mesh& data, unsigned int i);

private:
    std::vector<model::Mesh> _meshes;

    D3Devices* _devices;
    IndexBuffer_mk2* _indexBuffer;
    VertexResource<Pos>* _vertexResource;
};

} // namespace graphics