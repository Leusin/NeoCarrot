#pragma once

#include "D3D11Devices.h"
#include "CompileShader.h"

#include <d3d11.h>
#include <directxmath.h>
#include <wrl.h>

namespace graphics
{

class TextureShader: public CompileShader
{
public:
    TextureShader();
    TextureShader(const TextureShader&);
    ~TextureShader();

    void Initialize(ID3D11Device* device);
    void Render(ID3D11DeviceContext* deviceContext, int indexCount, DirectX::XMMATRIX world, DirectX::XMMATRIX view, DirectX::XMMATRIX proj, ID3D11ShaderResourceView* texture);
    void Finalize();

private:
    void CreateShader(ID3D11Device* device, const WCHAR* vsFile, const WCHAR* psFile);

    void SetShaderParameters(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX world, DirectX::XMMATRIX view, DirectX::XMMATRIX proj, ID3D11ShaderResourceView* texture);
    void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11SamplerState> _sampleState{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _matirxBuffer{ nullptr };

};

} // namespace graphics
