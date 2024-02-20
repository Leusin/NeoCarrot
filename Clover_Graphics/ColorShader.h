#pragma once

#include "D3D11Devices.h"
#include "ConstatntBufferType.h"
#include "CompileShader.h"

#include <d3d11.h>
#include <directxmath.h>
#include <wrl.h>

namespace graphics
{

class ColorShader: public CompileShader
{
public:
    ColorShader();
    ColorShader(const ColorShader&);
    ~ColorShader();

    void Initialize(ID3D11Device* device);
    void Render(ID3D11DeviceContext* deviceContext, int indexCount, DirectX::XMMATRIX world, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);
    void Finalize();

private:
    void CreateShader(ID3D11Device* device, const WCHAR* vsFile, const WCHAR* psFile);

    void SetShaderParameters(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX world, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);
    void RenderShader(ID3D11DeviceContext* deviceContext, int);

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };
    
    // 상수 버퍼
    Microsoft::WRL::ComPtr<ID3D11Buffer> _matirxBuffer{ nullptr };
};

} // namespace graphics
