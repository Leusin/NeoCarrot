#pragma once

#include "DDSTexture.h"

#include <directxmath.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <wrl.h>
#include <memory>

namespace graphics
{

class ModelMeshPart
{
public:
    ModelMeshPart() noexcept;
    
    ModelMeshPart(ModelMeshPart&&)            = default;
    ModelMeshPart& operator=(ModelMeshPart&&) = default;

    ModelMeshPart(const ModelMeshPart&)            = default;
    ModelMeshPart& operator=(const ModelMeshPart&) = default;
    
    virtual ~ModelMeshPart();

    uint32_t indexCount{ 0 };
    uint32_t startIndex{ 0 };
    int32_t vertexOffset{ 0 };
    uint32_t vertexStride{ 0 };
    D3D_PRIMITIVE_TOPOLOGY primitiveType;
    DXGI_FORMAT indexFormat;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer{ nullptr };
    bool isAlpha{ false };

    using Collection = std::vector<std::unique_ptr<ModelMeshPart>>;
};

class ModelMesh
{
public:
    ModelMesh() noexcept;

    ModelMesh(ModelMesh&&)            = default;
    ModelMesh& operator=(ModelMesh&&) = default;

    ModelMesh(const ModelMesh&)            = default;
    ModelMesh& operator=(const ModelMesh&) = default;

    virtual ~ModelMesh();

    ModelMeshPart::Collection meshParts;
    uint32_t _boneIndex;
    std::vector<uint32_t> _boneInfluences;
    std::wstring _name;
    bool _ccw;
    bool _pmalpha;

    using Collection = std::vector<std::shared_ptr<ModelMesh>>;
};

class Model
{
public:
    Model() = default;

    Model(Model&&)            = default;
    Model& operator=(Model&&) = default;

    Model(const Model& other);
    Model& operator=(const Model& rhs);

    virtual ~Model();

    ModelMesh::Collection meshes;

    std::wstring name;

    void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName);
    void Render(ID3D11DeviceContext* deviceContext);
    void Finalize();

    ID3D11ShaderResourceView* GetTexture();

private:
    void InitializeBuffers(ID3D11Device* device);
    void RenderBuffers(ID3D11DeviceContext* deviceContext);
    void LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileName);

    std::shared_ptr<DDSTexture> _ddsTexture{ nullptr };
};

} // namespace graphics