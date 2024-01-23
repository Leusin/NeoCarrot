#pragma once

#include "CompileShader.h"
#include "D3Devices.h"
#include "GetEntity.h"
#include "IComponent.h"
#include "InputLayouts.h"
#include "Mesh.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <wrl.h>
#include <directxmath.h>

namespace graphics
{
class ScriptTutorial06: public core::IComponent, public core::GetEntity, CompileShader
{
public:
    template<typename T>
    struct VertexBufferInfo
    {
        std::vector<T> vertices;
        std::vector<unsigned int> vertexOffset;
        unsigned int totalVertexCount{ 0 };
    };

    struct IndexBufferInfo
    {
        std::vector<WORD> indices;
        std::vector<unsigned int> indexOffset;
        std::vector<unsigned int> indexCount;
        unsigned int totalIndexCount{ 0 };
    };


public:
    ScriptTutorial06(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    void CreateVertexShader();
    void CreatePixelShader();
    void LoadFbxMeshData();
    void SetVertexBuffer(model::Mesh& data);
    void SetIndexBuffer(model::Mesh& data);
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateConstantBuffer();

    void SetInputLayout();
    void SetVertexBuffer();
    void SetIndexBuffer();
    void SetPrimitiveTopology();

    void UpdateTransformAnimation(float dt);
    void UpdateConstantVariable();
    void Render();

    D3Devices* _d3devices{ nullptr };
    ID3D11DeviceContext* _deviceContext;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShaderSolid{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer{ nullptr };

    VertexBufferInfo<Nol> _vbInfo;
    IndexBufferInfo _ibInfo;

    std::vector<DirectX::XMFLOAT4> vLightDirs;
    std::vector<DirectX::XMFLOAT4> vLightColors;
    //DirectX::XMFLOAT4 vLightDirs[2];
    //DirectX::XMFLOAT4 vLightColors[2];

    ConstBuffLit _cb;
};

} // namespace graphics