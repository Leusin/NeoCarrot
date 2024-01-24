/// 2024-01-24


#pragma once

#include "AllComponents.h"
#include "AllBufferStruct.h"
#include "CompileShader.h"
#include "GetEntity.h"
#include "IComponent.h"

namespace graphics
{
// 전방 선언
template<typename V>
class VertexBuffer;
class IndexBuffer;

// 본문
class GridScript: public core::IComponent, core::GetEntity, CompileShader
{
private:
    struct PosCol: public Pos, public Col
    {
    };

public:
    GridScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    void CreateVertexShader(const std::wstring& file);
    void CreatePixelShader(const std::wstring& file);
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateConstantBuffer();

    void SetInputLayout();
    void SetVertexBuffers();
    void SetIndexBuffers();
    void SetPrimitiveTopology();

    void SetConstantVariable();
    void UpdateRender();

private:
    D3Devices* _d3devices{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer{ nullptr };
};

} // namespace graphics