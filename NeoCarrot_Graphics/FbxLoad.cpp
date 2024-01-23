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
    assert(_devices && "FbxLoad �� D3Devices �� �ʿ����");
    assert(_vertexResource && "FbxLoad �� Vertex Resource �� �ʿ����");
    assert(_indexBuffer && "FbxLoad �� Index Buffer �� �ʿ����");

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
    // �а� �ִ� �޽��� ���� ũ��
    unsigned int vcount = static_cast<unsigned int>(data.vertices.size());

    // �а� �ִ� �Žð� ���۵� ���� ����
    _vertexResource->_vertexOffset.emplace_back(_vertexResource->_totalVertexCount);

    // ��ü ���� ��
    _vertexResource->_totalVertexCount += vcount;

    /// TODO
    ///    ��� ���ؽ� ����ü Ÿ�Ժ��� �Ľ��� �������� tobe continue
    ///    - enumclass �� switch?
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
    // �а� �ִ� �޽��� ���� ũ��
    unsigned int idxCount = static_cast<unsigned int>(data.faces.size());

    // �а� �ִ� �Žð� ���۵� �ε��� ����
    _indexBuffer->_indexOffset.emplace_back(_indexBuffer->_totalIndexCount);

    // �а� �ִ� �޽ð� ���� �� �ε��� ��
    _indexBuffer->_indexCount.emplace_back(3 * idxCount);

    // ��ü �ε��� ��
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