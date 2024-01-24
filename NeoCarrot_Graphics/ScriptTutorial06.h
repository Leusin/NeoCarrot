#pragma once

#include "AllBufferStruct.h"
#include "CompileShader.h"
#include "ConstantBufferStruct.h"
#include "D3Devices.h"
#include "GetEntity.h"
#include "IComponent.h"
#include "Mesh.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <vector>
#include <wrl.h>

namespace graphics
{
class ScriptTutorial06: public core::IComponent, public core::GetEntity, CompileShader
{

private:
    struct PosNol: public Pos, public Nol
    {
    };

public:
    template<typename T>
    struct VertexBufferInfo
    {
        // 초기화할 때 사용
        std::vector<T> vertices;
        unsigned int totalVertexCount{ 0 };

        // 랜더 할 때 사용
        std::vector<unsigned int> vertexOffset;
    };

    struct IndexBufferInfo
    {
        // 초기화할 때 사용
        std::vector<WORD> indices;
        unsigned int totalIndexCount{ 0 };

        // 랜더 할 때 사용
        std::vector<unsigned int> indexOffset;
        std::vector<unsigned int> indexCount;
    };


public:
    ScriptTutorial06(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    void CreateVertexShader();
    void CreatePixelShader();
    void LoadFbxMeshData();
    void LoadVertexBuffer(model::Mesh& data);
    void LoadIndexBuffer(model::Mesh& data);
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateConstantBuffer();

    void SetInputLayout();
    void SetVertexBuffers();
    void SetIndexBuffers();
    void SetPrimitiveTopology();

    void SetParameter();

    void UpdateTransformAnimation(float dt);
    void UpdateConstantVariable();
    void Render();

    D3Devices* _d3devices{ nullptr };
    ID3D11DeviceContext* _deviceContext;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShaderSolid{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer{ nullptr };

    VertexBufferInfo<Nol> _vbInfo;
    IndexBufferInfo _ibInfo;

    std::vector<DirectX::XMFLOAT4> vLightDirs;
    std::vector<DirectX::XMFLOAT4> vLightColors;

    ConstBuffLit _cb;
};

} // namespace graphics