#include "Effect.h"

#include "D3Devices.h"
#include "Transpose.h"

#include <d3dcompiler.h>
#include <fstream>
#include <vector>

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
Effect::Effect(EntityPtr entityPtr, std::wstring fileName) :
GetEntity(EntityPtr(entityPtr)),
_fileName(fileName),
_d3device{GetComponent<graphics::D3Devices>()}
{
    assert(_d3device && "Effect 에서 D3Devices 를 찾을 수 없음");

#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd Effect Component\n";
#endif // _DEBUG
}

void Effect::Awake()
{
    AwakeReadFile();
    AwakeGetTechniqueByName();
}

void Effect::Update(float dt)
{
    UpdateSetWorldViewProj();
}

bool Effect::CompileFromFile()
{
    Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob{nullptr};
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{nullptr};

    HRESULT hr = D3DCompileFromFile(_fileName.c_str(),         // HLSL 파일 경로
                                    nullptr,                   // 매크로 정의 (보통은 nullptr)
                                    nullptr,                   // include 파일 (보통은 nullptr)
                                    "main",                    // 진입점 함수 이름
                                    "ps_5_0",                  // 컴파일할 프로파일
                                    0,                         // 플래그 (보통은 0)
                                    0,                         // 플래그 (보통은 0)
                                    shaderBlob.GetAddressOf(), // 컴파일된 쉐이더 코드를 저장할 버퍼
                                    errorBlob.GetAddressOf()   // 컴파일 에러 메시지를 저장할 버퍼
    );

    // 컴파일 결과 확인
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
            errorBlob->Release();
        }
        // 오류 처리
        // ...

        return false;
    }

    return true;
}

void Effect::AwakeGetTechniqueByName()
{

    _tech            = _fx->GetTechniqueByName("ColorTech");
    _fxWorldViewProj = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Effect::UpdateSetWorldViewProj()
{
    auto worldViewProj = GetComponent<Transpose>()->WorldViewProj();
    _fxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));
}

void Effect::AwakeReadFile()
{
    std::ifstream fin(_fileName, std::ios::binary);

    if (!fin)
    {
        if (CompileFromFile())
            MessageBox(0, L"파일을 찾을 수 없으센.", 0, 0);
    }

    fin.seekg(0, std::ios_base::end);
    int size = (int)fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    std::vector<char> compiledShader(size);

    fin.read(&compiledShader[0], size);
    fin.close();

    HRESULT result = D3DX11CreateEffectFromMemory(&compiledShader[0],     // 컴파일된 효과 데이터 Blob
                                                  size,                   // Blob 의 길이
                                                  0,                      // 이펙트 플래그
                                                  _d3device->GetDevice(), // 디바이스 포인터
                                                  _fx.GetAddressOf()); // 새로 만든 이펙트 인터페이스 주소

    assert(_fx);
}

void Effect::GetTechniqueDesc(D3DX11_TECHNIQUE_DESC* des)
{
    _tech->GetDesc(des);
}

} // namespace graphics