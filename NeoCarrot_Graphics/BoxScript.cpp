#include "BoxScript.h"

#include "FbxLoader.h"
#include "StructedBuffer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Transpose.h"
#include "InputLayout.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

BoxScript::BoxScript(EntityPtr entityPtr, loader::FbxLoader* fbxLoader)
    : GetEntity(EntityPtr(entityPtr))
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::PosNormal>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
{

    std::vector<model::Mesh> mesh = fbxLoader->GetMeshAll("../NeoCarrot_Graphics/FBX/a.fbx");

    SetVertexBuffer(mesh);
    SetIndexBuffer(mesh);

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd BoxScript Component\n";
#endif // _DEBUG;
}

void BoxScript::Awake()
{
}
void BoxScript::Update(float dt)
{
}

void BoxScript::SetVertexBuffer(std::vector<model::Mesh>& data)
{
    // 읽고 있는 메시의 정점 크기
    UINT vcount = static_cast<UINT>(data[0].vertices.size());

    // 읽고 있는 매시가 시작될 정점 숫자
    auto vertexOffset = _vertexBuffer->_vertexOffset;
    auto totalVertexCount = _vertexBuffer->_totalVertexCount;
    vertexOffset.push_back(totalVertexCount);

    // 전체 정점 수
    _totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        _vertices.push_back(
            vertexInputElement::Vertex{DirectX::XMFLOAT3{meshData->_opt_vertex[i]->_pos},
                                       DirectX::XMFLOAT3{meshData->_opt_vertex[i]->_normal},
                                       DirectX::XMFLOAT2{meshData->_opt_vertex[i]->u, meshData->_opt_vertex[i]->v}});
    }
}
void BoxScript::SetIndexBuffer(std::vector<model::Mesh>& data)
{
    // 읽고 있는 메시의 정점 크기
    UINT idxCount = meshData->_mesh_numfaces;

    // 읽고 있는 매시가 시작될 인덱스 숫자
    _indexOffset.push_back(_totalIndexCount);

    // 읽고 있는 메시가 가질 총 인덱스 수
    _indexCount.push_back(3 * idxCount);

    // 전체 인덱스 수
    _totalIndexCount += (3 * idxCount);

    for (UINT i = 0; i < idxCount; ++i)
    {
        _indices.push_back(meshData->_opt_index[i].index[0]);
        _indices.push_back(meshData->_opt_index[i].index[2]);
        _indices.push_back(meshData->_opt_index[i].index[1]);
    }
}

} // namespace graphics