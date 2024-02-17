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
    // 1. ���̴��� ������
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };
    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };

    CompileShaderFromFile(vsFile, "VS", "vs_5_0", pVSBlob.GetAddressOf());
    CompileShaderFromFile(psFile, "PS", "ps_5_0", pPSBlob.GetAddressOf());

    assert(pVSBlob.Get() && "���ؽ� ���̴��� ID3DBlob �� �� �ͱ۾���");
    assert(pPSBlob.Get() && "�ȼ� ���̴��� ID3DBlob �� �� �ͱ۾���");

    //
    // 2. ���̴� ��ü�� ����
    //
    device->CreateVertexShader(pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        nullptr,
        _vertexShader.GetAddressOf());
    device->CreatePixelShader(pPSBlob->GetBufferPointer(),
        pPSBlob->GetBufferSize(),
        nullptr,
        _pixelShader.GetAddressOf());

    assert(_pixelShader.Get() && "ID3D11PixelShader �� �� �ͱ۾���");
    assert(_vertexShader.Get() && "ID3D11VertexShader �� �� �ͱ۾���");

    //
    // 3. ���ؽ� ��ǲ ���̾ƿ��� ����
    //
    device->CreateInputLayout(PosTexDesc.data(),
        static_cast<unsigned int>(PosTexDesc.size()),
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        _vertexLayout.GetAddressOf());

     assert(_vertexLayout.Get() && "ID3D11InputLayout �� �� �ͱ۾���");

    //
    // 4. ��� ���� ����
    //
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage             = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth         = sizeof(MatrixBufferType);
    bufferDesc.BindFlags         = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags    = 0;
    device->CreateBuffer(&bufferDesc, nullptr, _matirxBuffer.GetAddressOf());

    assert(_matirxBuffer.Get() && "��� ���ۿ� �ϰ͵� ����");

    //
    // 5.�ؽ�ó ���÷� ������Ʈ ����
    //

    // �ؽ�ó ���÷� ������Ʈ ����ü ����
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

    assert(_sampleState.Get() && "ID3D11SamplerState �� �ȸͱ۾���");
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

    // ��� ���� ��ġ
    unsigned int bufferNum{ 0 };
    // ���ؽ� ���̴��� ��� ���� ����
    deviceContext->VSSetConstantBuffers(bufferNum, 1, _matirxBuffer.GetAddressOf());

    // �ȼ����̴����� ���̴� �ؽ�ó ���ҽ� ����
    deviceContext->PSSetShaderResources(0, 1, &texture);

}

void TextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // ���ؽ� ���̾ƿ� ����
    deviceContext->IASetInputLayout(_vertexLayout.Get());

    // ���ؽ� ���̴��� �ȼ� ���̴� ����
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    // �ʼ� ���̴����� ���÷� ������Ʈ ����
    deviceContext->PSSetSamplers(0, 1, _sampleState.GetAddressOf());

    // �׸���
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

} // namespace graphics