#include "ScriptTutorial06.h"

#include "FbxLoader.h"
#include "components.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
ScriptTutorial06::ScriptTutorial06(EntityPtr entityPtr)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
    , _deviceContext{ _d3devices->GetDeviceContext() }
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd ScriptTutorial06 Component\n";
#endif // _DEBUG;
}

void ScriptTutorial06::Awake()
{
    CreateVertexShader();
    CreatePixelShader();
    LoadFbxMeshData();
    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateConstantBuffer();
}

void ScriptTutorial06::Update(float dt)
{
    SetVertexBuffer();
    SetIndexBuffer();
    SetPrimitiveTopology();

    UpdateTransformAnimation(dt);
    UpdateConstantVariable();
    Render();
}

void ScriptTutorial06::CreateVertexShader()
{
    //
    // 1. CompileVertexShader
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };

    CompileShaderFromFile(L"../NeoCarrot_Graphics/HLSL/Tutoroal06.hlsl",
                          "VS",
                          "vs_5_0",
                          pVSBlob.GetAddressOf());

    assert(pVSBlob.Get());

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
    device->CreateInputLayout(PosNormalDesc.data(),
                              static_cast<unsigned int>(PosNormalDesc.size()),
                              pVSBlob->GetBufferPointer(),
                              pVSBlob->GetBufferSize(),
                              _vertexLayout.GetAddressOf());

    assert(_vertexLayout.Get());
}

void ScriptTutorial06::CreatePixelShader()
{
    //
    // 4. CompilePxielShader
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };

    CompileShaderFromFile(L"../NeoCarrot_Graphics/HLSL/Tutoroal06.hlsl",
                          "PS",
                          "ps_5_0",
                          pPSBlob.GetAddressOf());

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

    //
    // 4. CompileAnotherPxielShader
    //
    pPSBlob->Release();

    CompileShaderFromFile(L"../NeoCarrot_Graphics/HLSL/Tutoroal06.hlsl",
                          "PSSolid",
                          "ps_5_0",
                          pPSBlob.GetAddressOf());

    assert(pPSBlob.Get() && "ID3DBlob 가 안 맹글어짐");

    //
    // 5. CreateAnotherPixelShader
    //

    device->CreatePixelShader(pPSBlob->GetBufferPointer(),
                              pPSBlob->GetBufferSize(),
                              nullptr,
                              _pixelShaderSolid.GetAddressOf());

    assert(_pixelShader.Get() && "ID3D11PixelShader 가 안 맹글어짐");
}

void ScriptTutorial06::LoadFbxMeshData()
{
    //
    // 6.LoadFbxMeshData
    //
    loader::FbxLoader fbxLoader;

    auto meshes = fbxLoader.GetMeshAll("../NeoCarrot_Graphics/FBX/a.fbx");

    for (auto& mesh : meshes)
    {
        SetVertexBuffer(mesh);
        SetIndexBuffer(mesh);
    }
}

void ScriptTutorial06::SetVertexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    unsigned int vcount = static_cast<unsigned int>(data.vertices.size());

    // 읽고 있는 매시가 시작될 정점 숫자
    _vbInfo.vertexOffset.emplace_back(_vbInfo.totalVertexCount);

    // 전체 정점 수
    _vbInfo.totalVertexCount += vcount;

    for (unsigned int i = 0; i < vcount; i++)
    {
        _vbInfo.vertices.emplace_back(Nol{
            DirectX::XMFLOAT3{ data.vertices[i].position.x,
                               data.vertices[i].position.y,
                               data.vertices[i].position.z },
            DirectX::XMFLOAT3{ data.vertices[i].normal.x,
                               data.vertices[i].normal.y,
                               data.vertices[i].normal.z } });
    }
}

void ScriptTutorial06::SetIndexBuffer(model::Mesh& data)
{
    // 읽고 있는 메시의 정점 크기
    unsigned int idxCount = static_cast<unsigned int>(data.faces.size());

    // 읽고 있는 매시가 시작될 인덱스 숫자
    _ibInfo.indexOffset.emplace_back(_ibInfo.totalIndexCount);

    // 읽고 있는 메시가 가질 총 인덱스 수
    _ibInfo.indexCount.emplace_back(3 * idxCount);

    // 전체 인덱스 수
    _ibInfo.totalIndexCount += (3 * idxCount);

    for (unsigned int i = 0; i < idxCount; ++i)
    {
        _ibInfo.indices.emplace_back(static_cast<WORD>(data.faces[i].indices[0]));
        _ibInfo.indices.emplace_back(static_cast<WORD>(data.faces[i].indices[1]));
        _ibInfo.indices.emplace_back(static_cast<WORD>(data.faces[i].indices[2]));
    }
}

void ScriptTutorial06::CreateVertexBuffer()
{
    //
    // 7. CreateVertexBuffer
    //
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Nol) * static_cast<unsigned int>(_vbInfo.vertices.size());
    bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = _vbInfo.vertices.data();
    device->CreateBuffer(&bd, &InitData, _vertexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get() && "버텍스 버퍼에 암것도 없음");
}

void ScriptTutorial06::CreateIndexBuffer()
{
    //
    // 8. CreateIndexBuffer
    //
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd;
    bd.Usage     = D3D11_USAGE_IMMUTABLE;
    bd.ByteWidth = sizeof(UINT) * static_cast<UINT>(_ibInfo.indices.size());
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags      = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = _ibInfo.indices.data();

    device->CreateBuffer(&bd, &iinitData, _indexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get() && "인덱스 버퍼에 암것도 없음");
}

void ScriptTutorial06::CreateConstantBuffer()
{
    //
    // 8. CreateConstantBuffer
    //
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(ConstBuffLit);
    bd.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags    = 0;
    device->CreateBuffer(&bd, nullptr, _constantBuffer.GetAddressOf());

     assert(_constantBuffer.Get() && "상수 버퍼에 암것도 없음");

    vLightDirs = {
        DirectX::XMFLOAT4(-0.25f, 0.25f, -0.25f, 0.5f),
        DirectX::XMFLOAT4(0.0f, 0.0f, -0.5f, 0.5f),
    };

    vLightColors = { DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
                     DirectX::XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f) };
}

void ScriptTutorial06::SetInputLayout()
{
    _deviceContext->IASetInputLayout(_vertexLayout.Get());
}

void ScriptTutorial06::SetVertexBuffer()
{
    UINT stride = sizeof(Nol);
    UINT offset = 0;
    _deviceContext
        ->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
}

void ScriptTutorial06::SetIndexBuffer()
{
    _deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void ScriptTutorial06::SetPrimitiveTopology()
{
    _deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ScriptTutorial06::UpdateTransformAnimation(float dt)
{
    auto transpose = GetComponent<Transpose_mk2>();

    static float t;
    t += dt;

    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationY(-2.0f * t);
    transpose->SetWorld(DirectX::XMMatrixRotationY(t));
    DirectX::XMVECTOR vLightDir = DirectX::XMLoadFloat4(&vLightDirs[1]);
    vLightDir                   = XMVector3Transform(vLightDir, mRotate);
    DirectX::XMStoreFloat4(&vLightDirs[1], vLightDir);
}

void ScriptTutorial06::UpdateConstantVariable()
{
    auto transpose = GetComponent<Transpose_mk2>();

    _cb.mWorld         = XMMatrixTranspose(transpose->GetWorld());
    _cb.mView          = XMMatrixTranspose(transpose->GetView());
    _cb.mProjection    = XMMatrixTranspose(transpose->GetProj());
    _cb.vLightDir[0]   = vLightDirs[0];
    _cb.vLightDir[1]   = vLightDirs[1];
    _cb.vLightColor[0] = vLightColors[0];
    _cb.vLightColor[1] = vLightColors[1];
    _cb.vOutputColor   = DirectX::XMFLOAT4(0, 0, 0, 0);
    _deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &_cb, 0, 0);
}

void ScriptTutorial06::Render()
{
    _deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    _deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
    _deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
    _deviceContext->PSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());

    for (unsigned int i = 0; i < _vbInfo.vertexOffset.size(); ++i)
    {
        _deviceContext->DrawIndexed(_ibInfo.indexCount[i], // 인덱스 개수
                                    _ibInfo.indexOffset[i], // 인덱스 시작 위치
                                    _vbInfo.vertexOffset[i]); // 색인들이 더해지는 정수 값
    }

    for (int m = 0; m < 2; m++)
    {
        DirectX::XMMATRIX mLight = DirectX::XMMatrixTranslationFromVector(
            /*5.0f * */XMLoadFloat4(&vLightDirs[m]));

        DirectX::XMMATRIX mLightScale = DirectX::XMMatrixScaling(0.2f, 0.2f, 0.2f);
        mLight = mLightScale * mLight;

        _cb.mWorld      = XMMatrixTranspose(mLight);
        _cb.vOutputColor = vLightColors[m];
        _deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &_cb, 0, 0);

        _deviceContext->PSSetShader(_pixelShaderSolid.Get(), nullptr, 0);
        
        _deviceContext->DrawIndexed(_ibInfo.indexCount[0], // 인덱스 개수
                                    _ibInfo.indexOffset[0], // 인덱스 시작 위치
                                    _vbInfo.vertexOffset[0]); // 색인들이 더해지는 정수 값
    }
}

} // namespace graphics