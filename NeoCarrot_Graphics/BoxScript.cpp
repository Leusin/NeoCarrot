#include "BoxScript.h"

#include "FbxLoader.h"
#include "components.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{

BoxScript::BoxScript(EntityPtr entityPtr, loader::FbxLoader* fbxLoader)
    : GetEntity(EntityPtr(entityPtr))
    , _devices{GetComponent<graphics::D3Devices>()}
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::Col>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
    , _effect{GetComponent<graphics::Effect>()}
{
    assert(_devices);
    assert(_vertexBuffer);
    assert(_indexBuffer);
    assert(_effect);

    std::vector<model::Mesh> mesh = fbxLoader->GetMeshAll("../NeoCarrot_Graphics/FBX/a.fbx");

    SetBuffers(mesh[0]);

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd BoxScript Component\n";
#endif // _DEBUG;
}

void BoxScript::Awake()
{
}

void BoxScript::Update(float dt)
{
    SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT offset = 0;
    SetBuffersToContext(offset);

    D3DX11_TECHNIQUE_DESC techDesc;
    _effect->GetTechniqueDesc(&techDesc);

    RenderWithEffectPasses(techDesc, offset);
}

void BoxScript::SetBuffers(model::Mesh& data)
{
    SetVertexBuffer(data);
    SetIndexBuffer(data);
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
            Col{
                DirectX::XMFLOAT3{
                data.vertices[i].position.x,
                data.vertices[i].position.y,
                data.vertices[i].position.z
            },
                DirectX::XMFLOAT4{
                1.f,
                1.f,
                1.f,
                1.f
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

void BoxScript::RenderWithEffectPasses(const D3DX11_TECHNIQUE_DESC& techDesc, UINT& offset)
{
    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        SetBuffersToContext(offset);

        _effect->_tech->GetPassByIndex(p)->Apply(0, _devices->GetDeviceContext());

        for (unsigned int i = 0; i < _vertexBuffer->_vertexOffset.size(); ++i)
        {
            DrawIndexed(i);
        }
    }
}

void BoxScript::SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY& primitiveTopology)
{
    _devices->SetPrimitiveTopology(primitiveTopology);
}

void BoxScript::DrawIndexed(const int& idx)
{
    _devices->GetDeviceContext()->DrawIndexed(_indexBuffer->_indexCount[idx],     // 인덱스 개수
                                              _indexBuffer->_indexOffset[idx],    // 인덱스 시작 위치
                                              _vertexBuffer->_vertexOffset[idx]); // 색인들이 더해지는 정수 값
}

} // namespace graphics