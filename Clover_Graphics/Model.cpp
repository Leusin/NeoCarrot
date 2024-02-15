#include "Model.h"
#include "VertexTypes.h"

namespace graphics
{

Model::Model(const Model& other)
{
}

Model& Model::operator=(const Model& rhs)
{
    // TODO: 여기에 return 문을 삽입합니다.

    return *this;
}

Model::~Model()
{
}

void Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName)
{
    InitializeBuffers(device);

    LoadTexture(device, deviceContext, fileName);
}

void Model::Finalize()
{
}

void Model::LoadTexture(ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    const WCHAR* fileName)
{
    _ddsTexture = std::make_shared<DDSTexture>();

    _ddsTexture->Initialize(device, deviceContext, fileName);
}

ID3D11ShaderResourceView* Model::GetTexture()
{
    if (_ddsTexture == nullptr)
    {
        return nullptr;
    }

    return _ddsTexture->GetTexture();
}

void Model::Render(ID3D11DeviceContext* deviceContext)
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
                (UINT)meshpart->vertexOffset);

            // 프리미티브 토폴로지 설정
            deviceContext->IASetPrimitiveTopology(meshpart->primitiveType);
        }
    }
}

void Model::InitializeBuffers(ID3D11Device* device)
{
    std::vector<DirectX::VertexPositionColorTexture> vertices = 
    {
        { 
            DirectX::XMFLOAT3{ -1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f },
            DirectX::XMFLOAT2{ 0.0f, 1.0f }
        },
        { 
            DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f },
            DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f } ,
            DirectX::XMFLOAT2{ 0.5f, 0.f }
        },
        { 
            DirectX::XMFLOAT3{ 1.0f, -1.0f, 0.0f },
            DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f },
            DirectX::XMFLOAT2{ 1.0f, 1.0f}
        }
    };

    std::vector<UINT> indices = { 0, 1, 2 };

    //
    // 메시 파트 생성
    //

    std::unique_ptr<ModelMeshPart> meshPart{ std::make_unique<ModelMeshPart>() };

    meshPart->indexCount = (uint32_t)indices.size();
    meshPart->startIndex;   // ??
    meshPart->vertexOffset; // = 0
    meshPart->vertexStride  = sizeof(DirectX::VertexPositionColorTexture);
    meshPart->indexFormat   = DXGI_FORMAT_R32_UINT;
    meshPart->primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    //
    // 버텍스 버퍼 생성
    //

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(DirectX::VertexPositionColorTexture) *
                   static_cast<unsigned int>(vertices.size());
    bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = vertices.data();

    device->CreateBuffer(&bd, &InitData, meshPart->vertexBuffer.GetAddressOf());

    assert(meshPart->vertexBuffer.Get() && "버텍스 버퍼에 암것도 없음");

    //
    // 인덱스 버퍼 생성
    //

    // D3D11_BUFFER_DESC bd;
    bd.Usage          = D3D11_USAGE_IMMUTABLE;
    bd.ByteWidth      = sizeof(UINT) * static_cast<UINT>(indices.size());
    bd.BindFlags      = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags      = 0;

    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices.data();

    device->CreateBuffer(&bd, &iinitData, meshPart->indexBuffer.GetAddressOf());

    assert(meshPart->indexBuffer.Get() && "인덱스 버퍼에 암것도 없음");

    //
    // 메시 생성
    //
    std::shared_ptr<ModelMesh> mesh{ std::make_shared<ModelMesh>() };
    mesh->meshParts.emplace_back(std::move(meshPart));
    meshes.emplace_back(mesh);
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