#pragma once

#include "D3Devices.h"
#include "GetEntity.h"
#include "IComponent.h"
#include "CompileShader.h"

#include <d3d11.h>
#include <string>
#include <type_traits>
#include <cassert>
#include <wrl.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace graphics
{

template<typename StructB>
class VertexResource: public core::IComponent, virtual core::GetEntity, public CompileShader
{
public:
    VertexResource(EntityPtr entityPtr,
                     const std::wstring shaderFile,
                     const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);

    void Awake() override;
    void Update(float dt) override;

public:
    void GetVerteices(const std::vector<StructB>& vertices);

private:
    // 1. 컴파일로 셰이더 생성
    // 2. 디바이스로 버텍스 버퍼 생성
    // 3. 디바이스로 인풋 레이아웃 생성
    // 4. 실제 버텍스 값 넣기. 어딘가에서 한다??? <-- GetVerteices
    // 5. 버텍스 버퍼 생성
    void InitilaizeVertexBuffer(const std::wstring& shaderFile,
                                const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc);
    void CreateVertexBuffer();

    void UpdateInputAssemBler();
    void SetShader();

private:
    D3Devices* _d3devices;

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer{ nullptr };

public:
    std::vector<StructB> _vertices;
    std::vector<unsigned int> _vertexOffset;
    unsigned int _totalVertexCount{ 0 };
};

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline VertexResource<StructB>::VertexResource(
    EntityPtr entityPtr,
    const std::wstring shaderFile,
    const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc)
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{ GetComponent<graphics::D3Devices>() }
{
    static_assert(std::is_class<StructB>::value &&
                  "VertexBuffer_mk2 의 템플릿 매개변수는 구조체(혹은 클래스)야함");

    InitilaizeVertexBuffer(shaderFile, desc);

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd VertexResource Component\n";
#endif // _DEBUG;
}

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline void VertexResource<StructB>::Awake()
{
    CreateVertexBuffer();
}

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline void VertexResource<StructB>::Update(float dt)
{
    UpdateInputAssemBler();
    SetShader();
}

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline void VertexResource<StructB>::InitilaizeVertexBuffer(
    const std::wstring& shaderFile,
    const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc)
{
    //
    // 1. CompileShader
    //
    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{ nullptr };
    CompileShaderFromFile(shaderFile.c_str(), "VS", "vs_5_0", pVSBlob.GetAddressOf());
    assert(pVSBlob.Get());

    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{ nullptr };
    CompileShaderFromFile(shaderFile.c_str(), "PS", "ps_5_0", pPSBlob.GetAddressOf());
    assert(pPSBlob.Get());

    //
    // 2. CreateShader
    //
    auto* device = _d3devices->GetDevice();

    device->CreateVertexShader(pVSBlob->GetBufferPointer(),
                               pVSBlob->GetBufferSize(),
                               nullptr,
                               _vertexShader.GetAddressOf());

    assert(_vertexShader.Get());

    //
    // 3. CreateInputLayout
    //
    device->CreateInputLayout(desc.data(),
                              static_cast<unsigned int>(desc.size()),
                              pVSBlob->GetBufferPointer(),
                              pVSBlob->GetBufferSize(),
                              _vertexLayout.GetAddressOf());

    assert(_vertexLayout.Get());

    device->CreatePixelShader(pPSBlob->GetBufferPointer(),
                              pPSBlob->GetBufferSize(),
                              nullptr,
                              _pixelShader.GetAddressOf());

    assert(_pixelShader.Get());
}

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline void VertexResource<StructB>::GetVerteices(
    const std::vector<StructB>& vertices)
{
    //
    // 4.  어딘가에서 _vertices 를 채워넣는다
    //
    _vertices = vertices;
}

//////////////////////////////////////////////////////////////////////
template<typename StructB>
inline void VertexResource<StructB>::CreateVertexBuffer()
{
    //
    // 5.CreateVertexBuffer
    //
    auto* device = _d3devices->GetDevice();

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(StructB) * static_cast<unsigned int>(_vertices.size());
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = _vertices.data();
    device->CreateBuffer(&bd, &InitData, _vertexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get() && "버텍스 버퍼에 암것도 없음");
}

template<typename StructB>
inline void VertexResource<StructB>::UpdateInputAssemBler()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    // UpdateInputAssemBler
    deviceContext->IASetInputLayout(_vertexLayout.Get());
    UINT stride = sizeof(StructB);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
}

template<typename StructB>
inline void VertexResource<StructB>::SetShader()
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
}

} // namespace graphics