#include "GetFbxMeshNol.h"

#include "InputLayoutStruct.h"
#include "VertexResource.h"

namespace graphics
{
GetFbxMeshNol::GetFbxMeshNol(EntityPtr entityPtr,
                             loader::FbxLoader* fbxLoader,
                             std::string file)
    : GetFbxMesh(entityPtr, fbxLoader, file)
{
    auto meshes = fbxLoader->GetMeshAll(file.c_str());
    for (auto& mesh : meshes)
    {
        SetVertexBuffer(mesh);
        SetIndexBuffer(mesh);
    }
}

void GetFbxMeshNol::SetVertexBuffer(model::Mesh& data)
{
    // �а� �ִ� �޽��� ���� ũ��

    auto rs = GetComponent<VertexResource<PosNol>>();

    // �а� �ִ� �Žð� ���۵� ���� ����
    rs->_vertexOffset.emplace_back(rs->_totalVertexCount);

    unsigned int vcount = static_cast<unsigned int>(data.vertices.size());

    // ��ü ���� ��
    rs->_totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        rs->_vertices.emplace_back(PosNol{
            DirectX::XMFLOAT3{ data.vertices[i].position.x,
                               data.vertices[i].position.y,
                               data.vertices[i].position.z },
            DirectX::XMFLOAT3{ data.vertices[i].normal.x,
                               data.vertices[i].normal.y,
                               data.vertices[i].normal.z } });
    }
}

} // namespace graphics