/// 2024-01-24


#pragma once

#include "AllComponents.h"
#include "CompileShader.h"
#include "GetEntity.h"
#include "IComponent.h"
#include "VertexBufferStruct.h"

#include <memory>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
class AxisScript: public core::IComponent, core::GetEntity, CompileShader
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

    // 생성 및 바인딩

    void CreateVertexShader(const std::wstring& file);
    void CreatePixelShader(const std::wstring& file);
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateConstantBuffer();

    // 업데이트 할 때 디바이스에 세팅

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