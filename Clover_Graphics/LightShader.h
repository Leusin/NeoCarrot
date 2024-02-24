#pragma once

#include "D3D11Devices.h"
#include "CompileShader.h"

#include <d3d11.h>
#include <directxmath.h>
#include <wrl.h>

namespace graphics
{

class LightShader: public CompileShader
{
public:
    LightShader();
    LightShader(const LightShader&);
    ~LightShader();

    void Initialize(ID3D11Device* device);
    void Render(ID3D11DeviceContext* deviceContext,
        int indexCount,
        DirectX::XMMATRIX world,
        DirectX::XMMATRIX view,
        DirectX::XMMATRIX proj,
        ID3D11ShaderResourceView* colorTexture,
        ID3D11ShaderResourceView* normalTexture,
        DirectX::XMFLOAT3 lightDir);
    void Finalize();

private:
    void CreateShader(ID3D11Device* device, const WCHAR* vsFile, const WCHAR* psFile);

    void SetShaderParameters(ID3D11DeviceContext* deviceContext,
        DirectX::XMMATRIX world,
        DirectX::XMMATRIX view,
        DirectX::XMMATRIX proj,
        ID3D11ShaderResourceView* colorTexture,
        ID3D11ShaderResourceView* normalTexture,
        DirectX::XMFLOAT3 lightDir);

    void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _layout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11SamplerState> _sampleState{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _matirxBuffer{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _lightBuffer{ nullptr };
};

} // namespace graphics