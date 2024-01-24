#include "AxisScript.h"

#include "AllComponents.h"

#include <DirectXColors.h>
#include <DirectXMath.h>
#include <vector>

namespace graphics
{

AxisScript::AxisScript(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _vertexBuffer{GetComponent<graphics::VertexBuffer<graphics::Col>>()}
    , _indexBuffer{GetComponent<graphics::IndexBuffer>()}
{
    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), 
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::Crimson)});

    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(static_cast<float>(INT_MAX), 0.0f, 0.0f),
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::Snow)});
    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::SeaGreen)});

    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(0.0f, static_cast<float>(INT_MAX), 0.0f),
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::Snow)});

    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), 
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::RoyalBlue)});

    _vertexBuffer->_vertices.push_back({
        DirectX::XMFLOAT3(0.0f, 0.0f, static_cast<float>(INT_MAX)),
        DirectX::XMFLOAT4((const float*)&DirectX::Colors::Snow)});

    _vertexBuffer->_totalVertexCount = static_cast<UINT>(_vertexBuffer->_vertices.size());

    _indexBuffer->_indices = {
        // x축
        0, 1,
        // y축
        2, 3,
        // z축
        4, 5,
    };

    _indexBuffer->_indexCount.emplace_back(static_cast<UINT>(_indexBuffer->_indices.size()));

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd AxisScript Component\n";
#endif // _DEBUG;
}

void AxisScript::Awake()
{
}

void AxisScript::Update(float dt)
{
    auto* dc          = GetComponent<D3Devices>()->GetDeviceContext();
    // InputLayout::SetInputLayout();
    GetComponent<D3Devices>()->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

    // 버퍼 디바이스에 묶기
    UINT offset = 0;
    _vertexBuffer->SetBuffers(offset);
    _indexBuffer->SetBuffers();

    auto worldViewProj   = GetComponent<Transpose_mk2>()->GetWorldViewProj();
    auto fxWorldViewProj = GetComponent<Effect>()->_fxWorldViewProj;
    fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    D3DX11_TECHNIQUE_DESC techDesc;
    auto                  tech = GetComponent<Effect>()->_tech;
    tech->GetDesc(&techDesc);

    for (UINT p = 0; p < techDesc.Passes; ++p)
    {
        tech->GetPassByIndex(p)->Apply(0, dc);

        // 6개의 인덱스로 축을 그린다.
        dc->DrawIndexed(6, 0, 0);
    }
}

} // namespace graphics