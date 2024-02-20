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
    // 1. ���̴��� ������
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };
    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };

    CompileShaderFromFile(vsFile, "VS", "vs_5_0", pVSBlob.GetAddressOf());
    CompileShaderFromFile(psFile, "PS", "ps_5_0", pPSBlob.GetAddressOf());

    assert(pVSBlob.Get());
    assert(pPSBlob.Get() && "ID3DBlob �� �� �ͱ۾���");


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
    device->CreateInputLayout(PosColorDesc.data(),
        static_cast<unsigned int>(PosNormalDesc.size()),
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        _vertexLayout.GetAddressOf());

    assert(_vertexLayout.Get());

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