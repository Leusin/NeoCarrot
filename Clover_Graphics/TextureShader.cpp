#include "TextureShader.h"
#include "VertexTypes.h"
#include "InputLayoutType.h"
#include "ConstatntBuffer.h"

namespace graphics
{

TextureShader::TextureShader()
{
}

TextureShader::TextureShader(const TextureShader&)
{
}

TextureShader::~TextureShader()
{
}

void TextureShader::Initialize(ID3D11Device* device)
{
    CreateShader(
        device, L"../Resource/HLSL/texture.hlsl", L"../Resource/HLSL/texture.hlsl");
}

void TextureShader::Render(ID3D11DeviceContext* deviceContext,
    int indexCount,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj,
    ID3D11ShaderResourceView* texture)
{
    SetShaderParameters(deviceContext, world, view, proj, texture);
    RenderShader(deviceContext, indexCount);
}

void TextureShader::Finalize()
{
    _vertexShader->Release();
    _pixelShader->Release();
    _vertexLayout->Release();
    _matirxBuffer->Release();
    _sampleState->Release();
}

void TextureShader::CreateShader(ID3D11Device* device,
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

    assert(pVSBlob.Get() && "버텍스 셰이더의 ID3DBlob 가 안 맹글어짐");
    assert(pPSBlob.Get() && "픽셀 셰이더의 ID3DBlob 가 안 맹글어짐");

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
    device->CreateInputLayout(PosTexDesc.data(),
        static_cast<unsigned int>(PosTexDesc.size()),
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        _vertexLayout.GetAddressOf());

     assert(_vertexLayout.Get() && "ID3D11InputLayout 가 안 맹글어짐");

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

    //
    // 5.텍스처 샘플러 스테이트 생성
    //

    // 텍스처 샘플러 스테이트 구조체 생성
    D3D11_SAMPLER_DESC samplerDesc;
    samplerDesc.Filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD         = 0;
    samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;

    device->CreateSamplerState(&samplerDesc, _sampleState.GetAddressOf());

    assert(_sampleState.Get() && "ID3D11SamplerState 가 안맹글어짐");
}

void TextureShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj, ID3D11ShaderResourceView* texture)
{
    MatrixBufferType matrixBuffer;

    matrixBuffer.world      = XMMatrixTranspose(world);
    matrixBuffer.view       = XMMatrixTranspose(view);
    matrixBuffer.projection = XMMatrixTranspose(proj);

    deviceContext->UpdateSubresource(
        _matirxBuffer.Get(), 0, nullptr, &matrixBuffer, 0, 0);

    // 상수 버퍼 위치
    unsigned int bufferNum{ 0 };
    // 버텍스 셰이더와 상수 버퍼 설정
    deviceContext->VSSetConstantBuffers(bufferNum, 1, _matirxBuffer.GetAddressOf());

    // 픽셀셰이더에서 셰이더 텍스처 리소스 설정
    deviceContext->PSSetShaderResources(0, 1, &texture);

}

void TextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // 버텍스 레이아웃 설정
    deviceContext->IASetInputLayout(_vertexLayout.Get());

    // 버텍스 셰이더와 픽셀 셰이더 설정
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    // 필셀 셰이더에서 샘플러 스테이트 설정
    deviceContext->PSSetSamplers(0, 1, _sampleState.GetAddressOf());

    // 그리기
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

} // namespace graphics