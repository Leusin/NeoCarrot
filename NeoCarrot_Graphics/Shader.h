// 셰이더의 초기화를 수행하는 함수를 호출합니다.

#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <string>
#include <wrl.h>

#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
// 전방 선언
class D3Devices;

// 본문
class Shader : public core::IComponent, virtual core::GetEntity
{
public:
    Shader(EntityPtr entityPtr, std::wstring vsFilename, std::wstring psFilename);

    void Awake() override;
    //void Update(float dt) override;

private:
    void CheckFiles();

    void CompileShader();
    void CreateShader();
    void CreateMatrixBuffer();

    D3Devices* _d3device{nullptr};

    // 셰이더 컴파일을 위한 변수

    std::wstring _vsFilename;
    std::wstring _psFilename;

     Microsoft::WRL::ComPtr<ID3DBlob> _errorMessage{nullptr};
     Microsoft::WRL::ComPtr<ID3DBlob> _vertexShaderBuffer{nullptr};
     Microsoft::WRL::ComPtr<ID3DBlob> _pixelShaderBuffer{nullptr};

    // 셰이더 생성을 위한 변수

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  _pixelShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11Buffer>       _matrixBuffer{nullptr};
};

} // namespace graphics