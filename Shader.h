#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <string>
#include <wrl.h>
#include <cassert>

namespace graphics
{
// 전방 선언
class D3Devices;

// 본문
template <typename V>
class Shader : public core::IComponent, virtual core::GetEntity
{
public:
    Shader(EntityPtr entityPtr, std::wstring vsFilename, std::wstring psFilename);

    void Awake() override;
    void Update(float dt) override;

private:
    D3Devices* _d3device{nullptr};

    std::wstring _vsFilename;
    std::wstring _psFilename;
};
template <typename V>
inline Shader<V>::Shader(EntityPtr entityPtr, std::wstring vsFilename, std::wstring psFilename) :
GetEntity(EntityPtr(entityPtr)),
_d3device{GetComponent<graphics::D3Devices>()},
_vsFilename{vsFilename},
_psFilename{psFilename}
{
    static_assert(std::is_class<V>::value, "Shader 가 받는 V 는 구조체(클래스)야 함");
    assert(_d3device && "Shader 에서 D3Devices 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Shader Component\n";
#endif // _DEBUG
}

template <typename V>
inline void Shader<V>::Awake()
{
    ID3D10Blob* errorMessage = nullptr;

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
    std::vector<D3D11_INPUT_ELEMENT_DESC> polygonLayout;

    //D3D11_INPUT_ELEMENT_DESC position;
    //position.SemanticName         = "POSITION";
    //position.SemanticIndex        = 0;
    //position.Format               = DXGI_FORMAT_R32G32B32_FLOAT;
    //position.InputSlot            = 0;
    //position.AlignedByteOffset    = 0;
    //position.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    //position.InstanceDataStepRate = 0;
    //polygonLayout.emplace_back(position);
    polygonLayout.emplace_back("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0);

    //polygonLayout[1].SemanticName         = "COLOR";
    //polygonLayout[1].SemanticIndex        = 0;
    //polygonLayout[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
    //polygonLayout[1].InputSlot            = 0;
    //polygonLayout[1].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
    //polygonLayout[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    //polygonLayout[1].InstanceDataStepRate = 0;
    polygonLayout
        .emplace_back("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0);

    // 레이아웃의 요소 수를 가져옵니다.
    unsigned int numElements = polygonLayout.size();

    // 정점 입력 레이아웃을 만듭니다.
    device->CreateInputLayout(polygonLayout.data(),
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
}

template <typename V>
inline void Shader<V>::Update(float dt)
{
}

} // namespace graphics