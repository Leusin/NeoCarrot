#include "Model.h"
#include "VertexTypes.h"

namespace graphics
{

Model::Model(const Model& other)
{
}

Model& Model::operator=(const Model& rhs)
{
    return *this;
}

Model::~Model()
{
}

void Model::Initialize(ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    const WCHAR* fileName)
{
    // 버텍스 버퍼와 인덱스 버퍼 초기화
    InitializeBuffers(device);

    // 텍스처 로드
    LoadTexture(device, deviceContext, fileName);
}

void Model::Render(ID3D11DeviceContext* deviceContext)
{
    RenderBuffers(deviceContext);
}

void Model::Finalize()
{
}

ID3D11ShaderResourceView* Model::GetTexture()
{
    if (_ddsTexture.get() == nullptr) return nullptr;

    return _ddsTexture->GetTexture();
}

void Model::InitializeBuffers(ID3D11Device* device)
{
    std::vector<DirectX::VertexPositionNormalTexture> vertices =
    {
        {
            DirectX::XMFLOAT3{ -1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f },
            DirectX::XMFLOAT2{ 0.0f, 1.0f }
        },
        {
            DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f },
            DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f },
            DirectX::XMFLOAT2{ 0.5f, 0.f }
        },
        {
            DirectX::XMFLOAT3{ 1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT3{ 0.0f, 0.0f, -1.0f },
            DirectX::XMFLOAT2{ 1.0f, 1.0f }
        }
    };

    /*
    std::vector<DirectX::VertexPositionTexture> vertices =
    {
        {
            DirectX::XMFLOAT3{ -1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT2{ 0.0f, 1.0f }
        },
        {
            DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f },
            DirectX::XMFLOAT2{ 0.5f, 0.f }
        },
        {
            DirectX::XMFLOAT3{ 1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT2{ 1.0f, 1.0f }
        }
    };
    */

    std::vector<UINT> indices = { 0, 1, 2 };

    //
    // 메시 파트 생성
    //
    std::unique_ptr<ModelMeshPart> meshPart{ std::make_unique<ModelMeshPart>() };

    meshPart->indexCount = (uint32_t)indices.size();
    meshPart->startIndex; // ??
    meshPart->vertexOffset  = 0;
    meshPart->vertexStride  = sizeof(DirectX::VertexPositionNormalTexture);
    meshPart->indexFormat   = DXGI_FORMAT_R32_UINT;
    meshPart->primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    //
    // 버텍스 버퍼 생성
    //
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage             = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormalTexture) *
                                 static_cast<unsigned int>(vertices.size());
    vertexBufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags      = 0;
    vertexBufferDesc.MiscFlags           = 0;
    vertexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vertexData = {};
    vertexData.pSysMem                = vertices.data();
    vertexData.SysMemPitch            = 0;
    vertexData.SysMemSlicePitch       = 0;

    device->CreateBuffer(
        &vertexBufferDesc, &vertexData, meshPart->vertexBuffer.GetAddressOf());

    assert(meshPart->vertexBuffer.Get() && "버텍스 버퍼에 암것도 없음");

    //
    // 인덱스 버퍼 생성
    //
    D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(UINT) * static_cast<UINT>(indices.size());
    indexBufferDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags      = 0;
    indexBufferDesc.MiscFlags           = 0;
    indexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA indexData = {};
    indexData.pSysMem                = indices.data();
    indexData.SysMemPitch            = 0;
    indexData.SysMemSlicePitch       = 0;

    device->CreateBuffer(
        &indexBufferDesc, &indexData, meshPart->indexBuffer.GetAddressOf());

    assert(meshPart->indexBuffer.Get() && "인덱스 버퍼에 암것도 없음");

    //
    // 메시 생성
    //
    std::shared_ptr<ModelMesh> mesh{ std::make_shared<ModelMesh>() };
    mesh->meshParts.emplace_back(std::move(meshPart));
    meshes.emplace_back(mesh);
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    for (auto& mesh : meshes)
    {
        for (auto& meshpart : mesh->meshParts)
        {
            // 입력 어셈블러에서 버텍스 버퍼 활성
            deviceContext->IASetVertexBuffers(0,
                1,
                meshpart->vertexBuffer.GetAddressOf(),
                &meshpart->vertexStride,
                (UINT*)&meshpart->vertexOffset);

            // 입력 어셈블러에서 인덱스 버퍼 활성
            deviceContext->IASetIndexBuffer(meshpart->indexBuffer.Get(),
                meshpart->indexFormat,
                0);

            // 프리미티브 토폴로지 설정
            deviceContext->IASetPrimitiveTopology(meshpart->primitiveType);
        }
    }
}

void Model::LoadTexture(ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    const WCHAR* fileName)
{
    _ddsTexture = std::make_shared<DDSTexture>();

    _ddsTexture->Initialize(device, deviceContext, fileName);
}

ModelMesh::ModelMesh() noexcept
{
}

ModelMesh::~ModelMesh()
{
}

ModelMeshPart::ModelMeshPart() noexcept
{
}

ModelMeshPart::~ModelMeshPart()
{
}

} // namespace graphics