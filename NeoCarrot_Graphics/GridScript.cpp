#include "GridScript.h"

#include "D3Devices.h"
#include "Effect.h"
#include "Entity.h"
#include "IndexBuffer.h"
#include "Transpose.h"
#include "VertexBuffer.h"
#include "InputLayout.h"
#include "StructedBuffer.h"

#include <DirectXColors.h>
#include <DirectXMath.h>
#include <vector>

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
GridScript::GridScript(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::PosCol>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
{
    SetVertexBuffer();
    SetIndexBuffer();

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd GridScript Component\n";
#endif // _DEBUG;
}
void GridScript::Awake()
{
}

void GridScript::Update(float dt)
{
    auto* dc          = GetComponent<D3Devices>()->GetDeviceContext();
    auto* inputLayout = GetComponent<InputLayout>()->_inputLayout.Get();
    dc->IASetInputLayout(inputLayout);
    dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    // �ε������ۿ� ���ؽ����� ����
    UINT stride = sizeof(PosCol);
    UINT offset = 0;

    // ���� ��ġ ����
    dc->IASetVertexBuffers(0, 1, _vertexBuffer->_vb.GetAddressOf(), &stride, &offset);
    dc->IASetIndexBuffer(_indexBuffer->_ib.Get(), DXGI_FORMAT_R32_UINT, 0);

    // WVP TM���� ����
    auto worldViewProj   = GetComponent<Transpose>()->WorldViewProj();
    auto fxWorldViewProj = GetComponent<Effect>()->_fxWorldViewProj;
    fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    // ����������Ʈ
    auto rState = GetComponent<D3Devices>()->_rasterizerState;
    dc->RSSetState(rState);

    D3DX11_TECHNIQUE_DESC techDesc;
    auto                  tech = GetComponent<Effect>()->_tech;
    tech->GetDesc(&techDesc);

    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        tech->GetPassByIndex(p)->Apply(0, dc);

        // 20���� �ε����� ���� �׸���.
        dc->DrawIndexed(40, 0, 0);
    }
}

void GridScript::SetVertexBuffer()
{
    _vertexBuffer->_vertices.resize(100);
    for (int i = 0; i < 100; i++)
    {
        _vertexBuffer->_vertices[i]
            .Pos = DirectX::XMFLOAT3(static_cast<float>(i % 10) - 5.0f, -0.f, static_cast<float>(i / 10) - 5.0f);
        _vertexBuffer->_vertices[i].Color = DirectX::XMFLOAT4((const float*)&DirectX::Colors::Orange);

    }

    _vertexBuffer->_totalVertexCount = static_cast<UINT>(_vertexBuffer->_vertices.size());

}
void GridScript::SetIndexBuffer()
{
    // �ε��� ���۸� �����Ѵ�.
    // 40���� ������ ��Ÿ������ �ߴ�.
    _indexBuffer->_indices.resize(40);
    for (int i = 0; i < 10; i++)
    {
        _indexBuffer->_indices[i * 2] = i;
        _indexBuffer->_indices[i * 2 + 1] = i + 90;
    }

    for (int i = 0; i < 10; i++)
    {
        _indexBuffer->_indices[20 + (i * 2)] = i * 10;
        _indexBuffer->_indices[20 + (i * 2) + 1] = i * 10 + 9;
    }

     _indexBuffer->_indexCount.emplace_back(static_cast<UINT>(_indexBuffer->_indices.size()));
}

} // namespace graphics