#include "ColorShader.h"
#include "VertexTypes.h"
#include "InputLayoutType.h"
#include "ConstatntBufferType.h"

namespace graphics
{

ColorShader::ColorShader()
{
}

ColorShader::ColorShader(const ColorShader&)
{
}

ColorShader::~ColorShader()
{
}

void ColorShader::Initialize(ID3D11Device* device)
{
    CreateShader(
        device, L"../Resource/HLSL/color.hlsl", L"../Resource/HLSL/color.hlsl");
}

void ColorShader::Render(ID3D11DeviceContext* deviceContext,
    int indexCount,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj)
{
    SetShaderParameters(deviceContext, world, view, proj);
    RenderShader(deviceContext, indexCount);
}

void ColorShader::Finalize()
{
    _vertexShader->Release();
    _pixelShader->Release();
    _vertexLayout->Release();
}

void ColorShader::CreateShader(ID3D11Device* device,
    const WCHAR* vsFile,
    const WCHAR* psFile)
{
    //
    // 1. 셰이더를 컴파일
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };
    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };

    CompileShaderFromFile(vsFile, "VS", "vs_5_0", pVSBlob.GetAddressOf());
    CompileShaderFromFile(psFile, "PS", "ps_5_0", pPSBlob.GetAddressOf());

    assert(pVSBlob.Get());
    assert(pPSBlob.Get() && "ID3DBlob 가 안 맹글어짐");


    //
    // 2. 셰이더 객체를 생성
    //
    device->CreateVertexShader(pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        nullptr,
        _vertexShader.GetAddressOf());
    device->CreatePixelShader(pPSBlob->GetBufferPointer(),
        pPSBlob->GetBufferSize(),
        nullptr,
        _pixelShader.GetAddressOf());

    assert(_pixelShader.Get() && "ID3D11PixelShader 가 안 맹글어짐");
    assert(_vertexShader.Get() && "ID3D11VertexShader 가 안 맹글어짐");

    //
    // 3. 버텍스 인풋 레이아웃을 생성
    //
    device->CreateInputLayout(PosColorDesc.data(),
        static_cast<unsigned int>(PosNormalDesc.size()),
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        _vertexLayout.GetAddressOf());

    assert(_vertexLayout.Get());

    //
    // 4. 상수 버퍼 생성
    //

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth         = sizeof(MatrixBufferType);
    bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags    = 0;
    device->CreateBuffer(&bufferDesc, nullptr, _matirxBuffer.GetAddressOf());

    assert(_matirxBuffer.Get() && "상수 버퍼에 암것도 없음");
}

void ColorShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj)
{
    MatrixBufferType matrixBuffer;

    matrixBuffer.world      = XMMatrixTranspose(world);
    matrixBuffer.view       = XMMatrixTranspose(view);
    matrixBuffer.projection = XMMatrixTranspose(proj);

    deviceContext->UpdateSubresource(
        _matirxBuffer.Get(), 0, nullptr, &matrixBuffer, 0, 0);
}

void ColorShader::RenderShader(ID3D11DeviceContext* deviceContext, int)
{
    deviceContext->IASetInputLayout(_vertexLayout.Get());

    unsigned int bufferNum{ 0 };
    deviceContext->VSSetConstantBuffers(bufferNum, 1, _matirxBuffer.GetAddressOf());
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    deviceContext->DrawIndexed(3, 0, 0);
}

} // namespace graphics