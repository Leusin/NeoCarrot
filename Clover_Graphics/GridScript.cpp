#include "GridScript.h"

#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
GridScript::GridScript(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd GridScript Component\n";
#endif // _DEBUG;
}

void GridScript::Awake()
{
    const std::wstring file = L"../NeoCarrot_Graphics/HLSL/color.fx";

    CreateVertexShader(file);
    CreatePixelShader(file);
    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateConstantBuffer();
}

void GridScript::Update(float dt)
{
    SetInputLayout();
    SetVertexBuffers();
    SetIndexBuffers();
    SetPrimitiveTopology();

    SetConstantVariable();

    UpdateRender();
}

#pragma region Awake

void GridScript::CreateVertexShader(const std::wstring& file)
{
    //
    // 1. CompileVertexShader
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };

    CompileShaderFromFile(file.c_str(), "VS", "vs_5_0", pVSBlob.GetAddressOf());

    assert(pVSBlob.Get() && "pVSBlob 가 안 맹글어짐");

    //
    // 2. CreateVertexShader
    //
    auto* device = _d3devices->GetDevice();

    device->CreateVertexShader(pVSBlob->GetBufferPointer(),
                               pVSBlob->GetBufferSize(),
                               nullptr,
                               _vertexShader.GetAddressOf());

    assert(_vertexShader.Get() && "ID3D11VertexShader 가 안 맹글어짐");

    //
    // 3. CreateInputLayout
    //
    device->CreateInputLayout(PosColorDesc.data(),
                              static_cast<unsigned int>(PosColorDesc.size()),
                              pVSBlob->GetBufferPointer(),
                              pVSBlob->GetBufferSize(),
                              _vertexLayout.GetAddressOf());

    assert(_vertexLayout.Get() && "ID3D11InputLayout 가 안 맹글어짐");
}

void GridScript::CreatePixelShader(const std::wstring& file)
{
    //
    // 4. CompilePxielShader
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };

    CompileShaderFromFile(file.c_str(), "PS", "ps_5_0", pPSBlob.GetAddressOf());

    assert(pPSBlob.Get() && "ID3DBlob 가 안 맹글어짐");

    //
    // 5. CreatePixelShader
    //
    auto* device = _d3devices->GetDevice();

    device->CreatePixelShader(pPSBlob->GetBufferPointer(),
                              pPSBlob->GetBufferSize(),
                              nullptr,
                              _pixelShader.GetAddressOf());

    assert(_pixelShader.Get() && "ID3D11PixelShader 가 안 맹글어짐");
}

void GridScript::CreateVertexBuffer()
{
    //
    // 6. CreateVertexBuffer
    //
    std::vector<PosCol> vertices;
    vertices.resize(100);

    for (int i = 0; i < 100; i++)
    {
        vertices[i] = 
        { 
            DirectX::XMFLOAT3(static_cast<float>(i % 10) - 5.0f, -0.f, static_cast<float>(i / 10) - 5.0f),
            DirectX::XMFLOAT4((const float*)&DirectX::Colors::Gray) 
            };
    }

    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(PosCol) * static_cast<unsigned int>(vertices.size());
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = vertices.data();
    device->CreateBuffer(&bd, &InitData, _vertexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get() && "버텍스 버퍼에 암것도 없음");
}

void GridScript::CreateIndexBuffer()
{
    //
    // 7. CreateIndexBuffer
    //
    std::vector<WORD> indices;
    indices.resize(40);

    for (int i = 0; i < 10; i++)
    {
        indices[i * 2]     = i;
        indices[i * 2 + 1] = i + 90;
    }

    for (int i = 0; i < 10; i++)
    {
        indices[20 + (i * 2)]     = i * 10;
        indices[20 + (i * 2) + 1] = i * 10 + 9;
    }

    D3D11_BUFFER_DESC bd;
    bd.Usage          = D3D11_USAGE_IMMUTABLE;
    bd.ByteWidth      = sizeof(UINT) * static_cast<UINT>(indices.size());
    bd.BindFlags      = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags      = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices.data();

    auto* device = _d3devices->GetDevice();

    device->CreateBuffer(&bd, &iinitData, _indexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get() && "인덱스 버퍼에 암것도 없음");
}

void GridScript::CreateConstantBuffer()
{
    //
    // 8. CreateConstantBuffer
    //
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(ConstBuffWorldViewProj);
    bd.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags    = 0;

    device->CreateBuffer(&bd, nullptr, _constantBuffer.GetAddressOf());

    assert(_constantBuffer.Get() && "상수 버퍼에 암것도 없음");
}

#pragma endregion Awake

#pragma region Update

void GridScript::SetInputLayout()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    _d3devices->GetDeviceContext()->IASetInputLayout(_vertexLayout.Get());
}

void GridScript::SetVertexBuffers()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    UINT stride = sizeof(PosCol);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
}

void GridScript::SetIndexBuffers()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void GridScript::SetPrimitiveTopology()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void GridScript::SetConstantVariable()
{
    //
    // BindWVPMatrix
    //
    auto* Trans = GetComponent<Transpose_mk2>();

    ConstBuffWorldViewProj cb;
    cb.WorldViewProj = DirectX::XMMatrixTranspose(Trans->GetWorldViewProj());

    auto* deviceContext = _d3devices->GetDeviceContext();

    deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
}

void GridScript::UpdateRender()
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    deviceContext->DrawIndexed(40, 0, 0);
}


#pragma endregion Update

} // namespace graphics