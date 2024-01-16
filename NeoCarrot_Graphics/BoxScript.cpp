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
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::PosNormal>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
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
    auto* dc          = GetComponent<D3Devices>()->GetDeviceContext();
    auto* inputLayout = GetComponent<InputLayout>()->_inputLayout.Get();
    dc->IASetInputLayout(inputLayout);
    dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    // �ε������ۿ� ���ؽ����� ����
    UINT stride = sizeof(PosCol);
    UINT offset = 0;

    // ���� ���� ��ġ ����
    dc->IASetVertexBuffers(0, 1, _vertexBuffer->_vb.GetAddressOf(), &stride, &offset);

    // �ε��� ���� ����
    dc->IASetIndexBuffer(_indexBuffer->_ib.Get(), DXGI_FORMAT_R32_UINT, 0);

    auto worldViewProj   = GetComponent<Transpose>()->WorldViewProj();
    auto fxWorldViewProj = GetComponent<Effect>()->_fxWorldViewProj;
    fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    auto rState = GetComponent<D3Devices>()->_rasterizerState;
    dc->RSSetState(rState);

    D3DX11_TECHNIQUE_DESC techDesc;
    auto                  tech = GetComponent<Effect>()->_tech;
    tech->GetDesc(&techDesc);

    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        // ���� ���� ��ġ ����
        dc->IASetVertexBuffers(0, 1, _vertexBuffer->_vb.GetAddressOf(), &stride, &offset);

        // �ε��� ���� ����
        dc->IASetIndexBuffer(_indexBuffer->_ib.Get(), DXGI_FORMAT_R32_UINT, 0);

        tech->GetPassByIndex(p)->Apply(0, dc);

        for (unsigned int i = 0; i < _vertexBuffer->_vertexOffset.size(); ++i)
        {
            dc->DrawIndexed(_indexBuffer->_indexCount[i],    // �ε��� ����
                            _indexBuffer->_indexOffset[i], // �ε��� ���� ��ġ
                            _vertexBuffer->_vertexOffset[i]); // ���ε��� �������� ���� �� 
        }
    }
}

void BoxScript::SetVertexBuffer(model::Mesh& data)
{
    // �а� �ִ� �޽��� ���� ũ��
    UINT vcount = static_cast<UINT>(data.vertices.size());

    // �а� �ִ� �Žð� ���۵� ���� ����
    _vertexBuffer->_vertexOffset.push_back(_vertexBuffer->_totalVertexCount);

    // ��ü ���� ��
    _vertexBuffer->_totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        _vertexBuffer->_vertices.push_back(
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

} // namespace graphics