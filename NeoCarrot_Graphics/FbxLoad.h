#pragma once

#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

namespace loader{class FbxLoader;}
namespace model{struct Mesh;}

namespace graphics
{
// ���� ����
class D3Devices;
class IndexBuffer_mk2;
template<typename V>
class VertexResource;
struct Pos;

class FbxLoad: public core::IComponent, virtual core::GetEntity
{
public:
    FbxLoad(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file);

public:
    void Awake() override;

private:
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);

private:
    D3Devices* _devices;
    IndexBuffer_mk2* _indexBuffer;
    VertexResource<Pos>* _vertexResource;
};

} // namespace graphics