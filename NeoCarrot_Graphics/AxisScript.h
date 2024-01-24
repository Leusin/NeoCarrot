#pragma once

#include "CompileShader.h"
#include "GetEntity.h"
#include "IComponent.h"
#include "VertexBufferStruct.h"
#include "AllComponents.h"

#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
// 전방 선언
template<typename V>
class VertexBuffer;
class IndexBuffer;

// 본문
class AxisScript: public core::IComponent, public core::GetEntity, CompileShader
{
private:
    struct PosCol: public Pos, public Col
    {
    };

public:
    AxisScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    void CreateVertexShader();
    void CreatePixelShader();
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateConstantBuffer();

    void BindInputLayout();
    void BindVertexBuffers();
    void BindIndexBuffers();
    void SetPrimitiveTopology();

    void BindConstantVariable();
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