#include "Shader.h"
#include "InputLayouts.h"
#include "D3Devices.h"

#include <type_traits>
#include <fstream>
#include <d3dcompiler.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DE


namespace graphics
{

Shader::Shader(EntityPtr entityPtr, std::wstring vsFilename, std::wstring psFilename) 
    : GetEntity(EntityPtr(entityPtr))
    , _d3device{GetComponent<graphics::D3Devices>()}
    , _vsFilename{vsFilename}
    , _psFilename{psFilename}
{
    assert(_d3device && "Shader 에서 D3Devices 를 찾을 수 없음");

    CheckFiles();

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Shader Component\n";
#endif // _DEBUG
}

inline void Shader::Awake()
{
    CompileShader();
    CreateShader();
    CreateMatrixBuffer();
}

void Shader::CheckFiles()
{
    std::ifstream vsFin(_vsFilename, std::ios::binary);
    std::ifstream psFin(_psFilename, std::ios::binary);

    if (!vsFin)
    {
        MessageBox(0, L" 버텍스 셰이더 파일을 찾을 수 없으센.", 0, 0);
    }

    if (!psFin)
    {
        MessageBox(0, L"픽셀 셰이더 파일을 찾을 수 없으센.", 0, 0);
    }

}

void Shader::CompileShader()
{
    // 버텍스 셰이더 코드를 컴파일 한다.
    D3DCompileFromFile(_vsFilename.c_str(),
                       nullptr,
                       nullptr,
                       "main",
                       "vs_5_0",
                       D3D10_SHADER_ENABLE_STRICTNESS,
                       0,
                       _vertexShaderBuffer.GetAddressOf(),
                       _errorMessage.GetAddressOf());

    //D3DCompile(_vsFilename.c_str(), _vsFilename.size(), "VertexShader", nullptr);

    assert(_vertexShaderBuffer.Get() && "Vertex Shader 컴파일 실패");

    // 픽셀 셰이더 코드를 컴파일 한다.
    D3DCompileFromFile(_psFilename.c_str(),
                       nullptr,
                       nullptr,
                       "main",
                       "ps_5_0",
                       D3D10_SHADER_ENABLE_STRICTNESS,
                       0,
                       _pixelShaderBuffer.GetAddressOf(),
                       _errorMessage.GetAddressOf());

    assert(_pixelShaderBuffer.Get() && "Pixel Shader 컴파일 실패");
}

void Shader::CreateShader()
{
    auto* device = _d3device->GetDevice();

    device->CreateVertexShader(_vertexShaderBuffer->GetBufferPointer(),
                               _vertexShaderBuffer->GetBufferSize(),
                               nullptr,
                               &_vertexShader);

    assert(_vertexShader.Get() && "Vertex Shader 생성 실패");

    device->CreatePixelShader(_pixelShaderBuffer->GetBufferPointer(),
                               _pixelShaderBuffer->GetBufferSize(),
                               nullptr,
                               &_pixelShader);

    assert(_pixelShader.Get() && "Pixel Shader 생성 실패");
}

void Shader::CreateMatrixBuffer()
{
    D3D11_BUFFER_DESC matrixBufferDesc;

    matrixBufferDesc.Usage               = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth           = sizeof(ConstantBuffer);
    matrixBufferDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags           = 0;
    matrixBufferDesc.StructureByteStride = 0;

    //matrixBufferDesc = {D3D11_USAGE_DYNAMIC, sizeof(MatrixBufferType),// D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, 0, 0};

     _d3device->GetDevice()->CreateBuffer(&matrixBufferDesc, nullptr, _matrixBuffer.GetAddressOf());

     assert(_matrixBuffer.Get() && "Matrix Buffer 생성 실패");
}

} // namespace graphics