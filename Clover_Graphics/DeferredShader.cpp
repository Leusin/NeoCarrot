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

    assert(_layout.Get() && "ID3D11InputLayout 가 안 맹글어짐");

    //
    // 4.텍스처 샘플러 스테이트 생성
    //

    // 텍스처 샘플러 스테이트 구조체 생성
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

    assert(_sampleState.Get() && "ID3D11SamplerState 가 안맹글어짐");

    //
    // 5. 상수 버퍼 생성
    //
    D3D11_BUFFER_DESC matrixBufferDesc = {};
    matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth           = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags           = 0;
    matrixBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&matrixBufferDesc, nullptr, _matirxBuffer.GetAddressOf());

    assert(_matirxBuffer.Get() && "상수 버퍼에 암것도 없음");
}

void DeferredShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
    DirectX::XMMATRIX world,
    DirectX::XMMATRIX view,
    DirectX::XMMATRIX proj,
    ID3D11ShaderResourceView* texture)
{
    //
    // 1. 변환 행렬 상수 버퍼
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

    // 픽셀 셰이더에서 셰이더 텍스처 리소스 설정
    deviceContext->PSSetShaderResources(0, 1, &texture);
}

void DeferredShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
    // 버텍스 레이아웃 설정
    deviceContext->IASetInputLayout(_layout.Get());

    // 버텍스 셰이더와 픽셀 셰이더 설정
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

    // 필셀 셰이더에서 샘플러 스테이트 설정
    deviceContext->PSSetSamplers(0, 1, _sampleState.GetAddressOf());

    // 그리기
    deviceContext->DrawIndexed(indexCount, 0, 0);
}

} // namespace graphics