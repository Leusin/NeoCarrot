#include "DeferredShader.h"
#include "VertexTypes.h"
#include "ConstatntBufferType.h"
#include "DeferredShader.h"

#include <vector>

namespace graphics
{

DeferredShader::DeferredShader()
{
}

DeferredShader::DeferredShader(const DeferredShader&)
{
}

DeferredShader::~DeferredShader()
{
}

void DeferredShader::Initialize(ID3D11Device* device)
{
    CreateShader(
        device, L"../Resource/HLSL/deferred.hlsl", L"../Resource/HLSL/deferred.hlsl");
}

void DeferredShader::Render(ID3D11DeviceContext* deviceContext,
    int indexCount,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj,
    ID3D11ShaderResourceView* texture)
{
    SetShaderParameters(
        deviceContext, world, view, proj, texture);

    RenderShader(deviceContext, indexCount);
}

void DeferredShader::Finalize()
{
    _vertexShader->Release();
    _pixelShader->Release();
    _layout->Release();
    _sampleState->Release();
    _matirxBuffer->Release();
}

void DeferredShader::CreateShader(ID3D11Device* device,
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

    std::vector<D3D11_INPUT_ELEMENT_DESC> polygonLayout = 
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    device->CreateInputLayout(polygonLayout.data(),
        static_cast<unsigned int>(polygonLayout.size()),
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        _layout.GetAddressOf());

    assert(_layout.Get() && "ID3D11InputLayout �� �� �ͱ۾���");

    //
    // 4.�ؽ�ó ���÷� ������Ʈ ����
    //

    // �ؽ�ó ���÷� ������Ʈ ����ü ����
    D3D11_SAMPLER_DESC samplerDesc;
    samplerDesc.Filter         = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
    samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias     = 0.f;
    samplerDesc.MaxAnisotropy  = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD         = 0;
    samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;

    device->CreateSamplerState(&samplerDesc, _sampleState.GetAddressOf());

    assert(_sampleState.Get() && "ID3D11SamplerState �� �ȸͱ۾���");

    //
    // 5. ��� ���� ����
    //
    D3D11_BUFFER_DESC matrixBufferDesc = {};
    matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth           = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags           = 0;
    matrixBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&matrixBufferDesc, nullptr, _matirxBuffer.GetAddressOf());

    assert(_matirxBuffer.Get() && "��� ���ۿ� �ϰ͵� ����");
}

void DeferredShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj,
    ID3D11ShaderResourceView* texture)
{
    //
    // 1. ��ȯ ��� ��� ����
    //
    //MatrixBufferType matrixBuffer;

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    deviceContext->Map(
        _matirxBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

    MatrixBufferType* dataPtr = reinterpret_cast<MatrixBufferType*>(mappedResource.pData);

    dataPtr->world      = XMMatrixTranspose(world);
    dataPtr->view       = XMMatrixTranspose(view);
    dataPtr->projection = XMMatrixTranspose(proj);

    deviceContext->Unmap(_matirxBuffer.Get(), 0);

    unsigned int bufferNum{ 0 };
    deviceContext->VSSetConstantBuffers(bufferNum, 1, _matirxBuffer.GetAddressOf());

    // �ȼ� ���̴����� ���̴� �ؽ�ó ���ҽ� ����
    deviceContext->PSSetShaderResources(0, 1, &texture);
}

void DeferredShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // ���ؽ� ���̾ƿ� ����
    deviceContext->IASetInputLayout(_layout.Get());

    // ���ؽ� ���̴��� �ȼ� ���̴� ����
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    // �ʼ� ���̴����� ���÷� ������Ʈ ����
    deviceContext->PSSetSamplers(0, 1, _sampleState.GetAddressOf());

    // �׸���
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

} // namespace graphics