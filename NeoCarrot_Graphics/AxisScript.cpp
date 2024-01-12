#include "AxisScript.h"

#include "D3Device.h"
#include "Effect.h"
#include "Entity.h"
#include "IndexBuffer.h"
#include "Transpose.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "VertexStruct.h"

#include <DirectXColors.h>
#include <DirectXMath.h>
#include <vector>

namespace graphics
{

AxisScript::AxisScript(EntityPtr entityPtr) :
_entity{EntityPtr(entityPtr)},
_vertexBuffer{_entity.lock()->GetComponent<graphics::VertexBuffer<graphics::PosCol>>()},
_indexBuffer{_entity.lock()->GetComponent<graphics::IndexBuffer>()}
{
    _vertexBuffer->_vertices.push_back(
        {DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Crimson)});

    _vertexBuffer->_vertices.push_back({DirectX::XMFLOAT3(static_cast<float>(INT_MAX), 0.0f, 0.0f),
                                        DirectX::XMFLOAT4((const float*)&DirectX::Colors::Crimson)});
    _vertexBuffer->_vertices.push_back(
        {DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::SeaGreen)});

    _vertexBuffer->_vertices.push_back({DirectX::XMFLOAT3(0.0f, static_cast<float>(INT_MAX), 0.0f),
                                        DirectX::XMFLOAT4((const float*)&DirectX::Colors::SeaGreen)});

    _vertexBuffer->_vertices.push_back(
        {DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::RoyalBlue)});

    _vertexBuffer->_vertices.push_back({DirectX::XMFLOAT3(0.0f, 0.0f, static_cast<float>(INT_MAX)),
                                        DirectX::XMFLOAT4((const float*)&DirectX::Colors::RoyalBlue)});

    _vertexBuffer->_totalVertexCount = _vertexBuffer->_vertices.size();

    _indexBuffer->_indices = {
        // x축
        0, 1,
        // y축
        2, 3,
        // z축
        4, 5,
    };

    _indexBuffer->_indexCount.emplace_back(_indexBuffer->_indices.size());

#ifdef _DEBUG
    std::cout << "\t\t\t\t\tAdd AxisScript Component\n";
#endif // _DEBUG;
}

void AxisScript::Awake()
{
#ifdef _DEBUG
    std::cout << "\t\t\t\t\tAxisScript Component Awake\n";
#endif // _DEBUG;
}

void AxisScript::Update(float dt)
{
    auto* dc          = _entity.lock()->GetComponent<D3Device>()->GetDeviceContext();
    auto* inputLayout = _entity.lock()->GetComponent<VertexLayout>()->_inputLayout.Get();
    dc->IASetInputLayout(inputLayout);
    dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    // 인덱스버퍼와 버텍스버퍼 셋팅
    UINT stride = sizeof(PosCol);
    UINT offset = 0;


    dc->IASetVertexBuffers(0, 1, _vertexBuffer->_vb.GetAddressOf(), &stride, &offset);

    dc->IASetIndexBuffer(_indexBuffer->_ib.Get(), DXGI_FORMAT_R32_UINT, 0);

    auto worldViewProj   = _entity.lock()->GetComponent<Transpose>()->WorldViewProj();
    auto fxWorldViewProj = _entity.lock()->GetComponent<Effect>()->_fxWorldViewProj;
    fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    auto rState = _entity.lock()->GetComponent<D3Device>()->_rasterizerState;
    dc->RSSetState(rState);

    D3DX11_TECHNIQUE_DESC techDesc;
    auto                  tech = _entity.lock()->GetComponent<Effect>()->_tech;
    tech->GetDesc(&techDesc);

    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        tech->GetPassByIndex(p)->Apply(0, dc);

        // 6개의 인덱스로 축을 그린다.
        dc->DrawIndexed(6, 0, 0);
    }
}

} // namespace graphics