#include "BoxScript.h"

#include "FbxLoader.h"
#include "StructedBuffer.h"

#include "D3Devices.h"
#include "Effect.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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
    , _devices{GetComponent<graphics::D3Devices>()}
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::PosNormal>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
    , _effect{GetComponent<graphics::Effect>()}
{
    std::vector<model::Mesh> mesh = fbxLoader->GetMeshAll("../NeoCarrot_Graphics/FBX/a.fbx");

    SetVertexBuffer(mesh[0]);
    SetIndexBuffer(mesh[0]);

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd BoxScript Component\n";
#endif // _DEBUG;
}

void BoxScript::Awake()
{
}

void BoxScript::Update(float dt)
{
    _devices->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT offset = 0;
    SetBuffersToContext(offset);

    //  TECH
    D3DX11_TECHNIQUE_DESC techDesc;
    _effect->GetTechniqueDesc(&techDesc);

    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        SetBuffersToContext(offset);

        // 테크 설정
        _effect->_tech->GetPassByIndex(p)->Apply(0, _devices->GetDeviceContext());

        for (unsigned int i = 0; i < _vertexBuffer->_vertexOffset.size(); ++i)
        {
            DrawIndexed(i);
        }
    }
}

void BoxScript::SetVertexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    UINT vcount = static_cast<UINT>(data.vertices.size());

    // 읽고 있는 매시가 시작될 정점 숫자
    _vertexBuffer->_vertexOffset.emplace_back(_vertexBuffer->_totalVertexCount);

    // 전체 정점 수
    _vertexBuffer->_totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        _vertexBuffer->_vertices.emplace_back(
            PosNormal{DirectX::XMFLOAT3{
                data.vertices[i].position.x,
                data.vertices[i].position.y,
                data.vertices[i].position.z
            },
            DirectX::XMFLOAT3{
                data.vertices[i].normal.x,
                data.vertices[i].normal.y,
                data.vertices[i].normal.z
            }});
    }
}

void BoxScript::SetIndexBuffer(model::Mesh& data)
{
    _indexBuffer->SetFromMesh(data);
}

void BoxScript::SetBuffersToContext(UINT& offset)
{
    _vertexBuffer->SetBuffers(offset);
    _indexBuffer->SetBuffers();
}

void BoxScript::DrawIndexed(const int& idx)
{
    _devices->GetDeviceContext()->DrawIndexed(_indexBuffer->_indexCount[idx],   // 인덱스 개수
                                              _indexBuffer->_indexOffset[idx],  // 인덱스 시작 위치
                                              _vertexBuffer->_vertexOffset[idx]); // 색인들이 더해지는 정수 값
}

} // namespace graphics