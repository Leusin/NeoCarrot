#include "ColorShader.h"

#include <d3dcompiler.h>

bool ColorShader::Initialize(ID3D11Device* device, HWND hwnd)
{
    ID3D10Blob* errorMessage = nullptr;

    auto vsFilename = L"./color.vs";
    auto psFilename = L"./color.ps";

    // 버텍스 쉐이더 코드를 컴파일 한다.
    ID3D10Blob* vertexShaderBuffer = nullptr;
    D3DCompileFromFile(vsFilename,
                       nullptr,
                       nullptr,
                       "VertexShader",
                       "vs_5_0",
                       D3D10_SHADER_ENABLE_STRICTNESS,
                       0,
                       &vertexShaderBuffer,
                       &errorMessage);

    // 픽셀 쉐이더 코드를 컴파일 한다.
    ID3D10Blob* pixelShaderBuffer = nullptr;
    D3DCompileFromFile(psFilename,
                       nullptr,
                       nullptr,
                       "PixelShader",
                       "ps_5_0",
                       D3D10_SHADER_ENABLE_STRICTNESS,
                       0,
                       &pixelShaderBuffer,
                       &errorMessage);

    // 버퍼로부터 정점 쉐이더를 생성한다.
    device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader);

    // 버퍼에서 픽셀 쉐이더를 생성한다.
    device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader);

    // 정점 입력 레이아웃 구조체를 설정합니다.
    // 이 설정은 ModelClass와 쉐이더의 VertexType 구조와 일치해야 한다.
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
    polygonLayout[0].SemanticName         = "POSITION";
    polygonLayout[0].SemanticIndex        = 0;
    polygonLayout[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[0].InputSlot            = 0;
    polygonLayout[0].AlignedByteOffset    = 0;
    polygonLayout[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[0].InstanceDataStepRate = 0;

    polygonLayout[1].SemanticName         = "COLOR";
    polygonLayout[1].SemanticIndex        = 0;
    polygonLayout[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
    polygonLayout[1].InputSlot            = 0;
    polygonLayout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    polygonLayout[1].InstanceDataStepRate = 0;

    // 레이아웃의 요소 수를 가져옵니다.
    unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

    // 정점 입력 레이아웃을 만듭니다.
    device->CreateInputLayout(polygonLayout,
                              numElements,
                              vertexShaderBuffer->GetBufferPointer(),
                              vertexShaderBuffer->GetBufferSize(),
                              &m_layout);

    // 더 이상 사용되지 않는 정점 쉐이더 버퍼와 픽셀 쉐이더 버퍼를 해제한다.
    vertexShaderBuffer->Release();
    vertexShaderBuffer = nullptr;

    pixelShaderBuffer->Release();
    pixelShaderBuffer = nullptr;

    // 정점 쉐이더에 있는 행렬 상수 버퍼의 구조체를 작성한다.
    D3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth           = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags           = 0;
    matrixBufferDesc.StructureByteStride = 0;

    // 상수 버퍼 포인터를 만들어 이 클래스에서 정점 쉐이더 상수 버퍼에 접근할 수 있게 한다.
    device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matrixBuffer);

    return true;
}

void ColorShader::Shutdown()
{
    m_matrixBuffer->Release();
    m_layout->Release();
    m_pixelShader->Release();
    m_vertexShader->Release();
}

bool ColorShader::Render(ID3D11DeviceContext* deviceContext,
                         int                  indexCount,
                         DirectX::XMMATRIX    worldMatrix,
                         DirectX::XMMATRIX    viewMatrix,
                         DirectX::XMMATRIX    projectionMatrix)
{
    // SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix))

    worldMatrix      = XMMatrixTranspose(worldMatrix);
    viewMatrix       = XMMatrixTranspose(viewMatrix);
    projectionMatrix = XMMatrixTranspose(projectionMatrix);

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    MatrixBufferType* dataPtr = reinterpret_cast<MatrixBufferType*>(mappedResource.pData);

    dataPtr->world      = worldMatrix;
    dataPtr->view       = viewMatrix;
    dataPtr->projection = projectionMatrix;

    deviceContext->Unmap(m_matrixBuffer, 0);

    unsigned bufferNumber{0};

    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

    // RenderShader(deviceContext, indexCount);

    // 정점 입력 레이아웃을 설정한다.
    deviceContext->IASetInputLayout(m_layout);

    // 삼각형을 그릴 정점 쉐이더와 픽셀 쉐이더를 설정한다.
    deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
    deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

    // 삼각형을 그린다.
    deviceContext->DrawIndexed(indexCount, 0, 0);

    return true;
}
