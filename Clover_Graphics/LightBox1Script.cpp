#include "LightBox1Script.h"

#include "Transpose_mk2.h"
#include "components.h"


#ifdef _DEBUG
#include "ColoredBox2Script.h"

#include <iostream>
#endif // _DEBUG

namespace graphics
{

LightBox1Script::LightBox1Script(EntityPtr entityPtr)
    : GetEntity{ EntityPtr(entityPtr) }
    , _transpose{ GetComponent<Transpose_mk2>() }
{
    InitializeBuffers();

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd LightBox1Script Component\n";
#endif // _DEBUG;
}

void LightBox1Script::Awake()
{
}

void LightBox1Script::Update(float dt)
{
    UpdateTick(dt);
    UpdateAnimation();
}

//////////////////////////////////////////////////////////////////////
void LightBox1Script::InitializeBuffers()
{
    auto* fbxMesh = GetComponent<GetFbxMesh>();
    auto meshes   = fbxMesh->_meshes;

    for (auto& mesh : meshes)
    {
        SetVertexBuffer(mesh);
        SetIndexBuffer(mesh);
    }
}

//////////////////////////////////////////////////////////////////////
void LightBox1Script::SetVertexBuffer(model::Mesh& data)
{
    // �а� �ִ� �޽��� ���� ũ��
    unsigned int vcount = static_cast<unsigned int>(data.vertices.size());

    auto vertexResource = GetComponent<VertexResource<Col>>();
    assert(vertexResource);

    // �а� �ִ� �Žð� ���۵� ���� ����
    vertexResource->_vertexOffset.emplace_back(vertexResource->_totalVertexCount);

    // ��ü ���� ��
    vertexResource->_totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        vertexResource->_vertices.emplace_back(Nol{
            DirectX::XMFLOAT3{ data.vertices[i].position.x,
                               data.vertices[i].position.y,
                               data.vertices[i].position.z },
            DirectX::XMFLOAT3{ data.vertices[i].normal.x,
                               data.vertices[i].normal.y,
                               data.vertices[i].normal.z } });
    }
}

//////////////////////////////////////////////////////////////////////
void LightBox1Script::SetIndexBuffer(model::Mesh& data)
{
    // �а� �ִ� �޽��� ���� ũ��
    unsigned int idxCount = static_cast<unsigned int>(data.faces.size());

    auto indexBuffer = GetComponent<IndexBuffer_mk2>();

    // �а� �ִ� �Žð� ���۵� �ε��� ����
    indexBuffer->_indexOffset.emplace_back(indexBuffer->_totalIndexCount);

    // �а� �ִ� �޽ð� ���� �� �ε��� ��
    indexBuffer->_indexCount.emplace_back(3 * idxCount);

    // ��ü �ε��� ��
    indexBuffer->_totalIndexCount += (3 * idxCount);

    for (unsigned int i = 0; i < idxCount; ++i)
    {
        indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[0]));
        indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[1]));
        indexBuffer->_indices.emplace_back(
            static_cast<WORD>(data.faces[i].indices[2]));
    }
}

//////////////////////////////////////////////////////////////////////
void LightBox1Script::UpdateTick(float dt)
{
    _t1 += dt * -1.f;
    _t2 += dt * -2.f;
}

//////////////////////////////////////////////////////////////////////
void LightBox1Script::UpdateAnimation()
{
    DirectX::XMMATRIX mSpin  = DirectX::XMMatrixRotationZ(_t1);
    DirectX::XMMATRIX mOrbit = DirectX::XMMatrixRotationY(_t2);
    DirectX::XMMATRIX mTranslate = DirectX::XMMatrixTranslation(-4.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX mScale = DirectX::XMMatrixScaling(0.3f, 0.3f, 0.3f);

    _transpose->SetWorld(mScale * mSpin * mTranslate * mOrbit);
}

void LightBox1Script::UpdateRender()
{
    auto* devices      = GetComponent<Devices>();
    auto deviceContext = devices->DeferredContext();

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    auto* indexBuf = GetComponent<IndexBuffer_mk2>();
    auto* vetexBuf = GetComponent<VertexResource<Pos>>();

    for (unsigned int i = 0; i < vetexBuf->_vertexOffset.size(); ++i)
    {
        deviceContext->DrawIndexed(indexBuf->_indexCount[i], // �ε��� ����
                                   indexBuf->_indexOffset[i], // �ε��� ���� ��ġ
                                   vetexBuf->_vertexOffset[i]); // ���ε��� �������� ���� ��
    }
}

} // namespace graphics