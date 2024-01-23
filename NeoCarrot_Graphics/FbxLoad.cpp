#include "FbxLoad.h"

#include "D3Devices.h"
#include "FbxLoader.h"
#include "IndexBuffer_mk2.h"
#include "InputLayouts.h"
#include "VertexResource.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
FbxLoad::FbxLoad(EntityPtr entityPtr, loader::FbxLoader* fbxLoader, std::string file)
    : GetEntity(EntityPtr(entityPtr))
    , _devices{ GetComponent<graphics::D3Devices>() }
    , _indexBuffer{ GetComponent<graphics::IndexBuffer_mk2>() }
    , _vertexResource{ GetComponent<graphics::VertexResource<Pos>>() }
{
    assert(_devices && "FbxLoad 는 D3Devices 를 필요로함");
    assert(_vertexResource && "FbxLoad 는 Vertex Resource 를 필요로함");
    assert(_indexBuffer && "FbxLoad 는 Index Buffer 를 필요로함");

     auto meshes = fbxLoader->GetMeshAll(file.c_str());
    for (auto& mesh : meshes)
    {
        SetVertexBuffer(mesh);
        SetIndexBuffer(mesh);
    }

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd FbxLoad Component\n";
#endif // _DEBUG;
}

void FbxLoad::Awake()
{
    
}

//////////////////////////////////////////////////////////////////////
void FbxLoad::SetVertexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    unsigned int vcount = static_cast<unsigned int>(data.vertices.size());

    // 읽고 있는 매시가 시작될 정점 숫자
    _vertexResource->_vertexOffset.emplace_back(_vertexResource->_totalVertexCount);

    // 전체 정점 수
    _vertexResource->_totalVertexCount += vcount;

    /// TODO
    ///    어떻케 버텍스 구조체 타입별로 파싱할 것인지는 tobe continue
    ///    - enumclass 와 switch?
    ///
    //if (data.hasColor && !data.hasNormal && !data.hasTangent && !data.hasTexture)
    {
        for (unsigned int i = 0; i < vcount; i++)
        {
            PushBackPosition(data, i);
        }   
    }
    // else if...
}

//////////////////////////////////////////////////////////////////////
void FbxLoad::SetIndexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    unsigned int idxCount = static_cast<unsigned int>(data.faces.size());

    // 읽고 있는 매시가 시작될 인덱스 숫자
    _indexBuffer->_indexOffset.emplace_back(_indexBuffer->_totalIndexCount);

    // 읽고 있는 메시가 가질 총 인덱스 수
    _indexBuffer->_indexCount.emplace_back(3 * idxCount);

    // 전체 인덱스 수
    _indexBuffer->_totalIndexCount += (3 * idxCount);

    for (unsigned int i = 0; i < idxCount; ++i)
    {
        _indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[0]));
        _indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[1]));
        _indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[2]));
    }
}

void FbxLoad::PushBackPosition(const model::Mesh& data, unsigned int i)
{
    _vertexResource->_vertices.emplace_back(Pos{ DirectX::XMFLOAT3{
        data.vertices[i].position.x,
        data.vertices[i].position.y,
        data.vertices[i].position.z } });
}

} // namespace graphics