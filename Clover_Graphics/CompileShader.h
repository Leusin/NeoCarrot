/// CompileShader.h : 셰이더 컴파일 함수 호출을 필료로 하는 클래스들을 위한 클래스.
/// 
/// 2024-01-22

#pragma once

#include <d3dcompiler.h>
#include <string>

namespace graphics
{

class CompileShader
{
protected:
/// <summary>
/// 상속해서 사용하는 것을 의도하기 때문에 직접 생성하는 것을 막음
/// </summary>
    CompileShader() = default;

public:
    HRESULT CompileShaderFromFile(const WCHAR* szFileName,
                                  LPCSTR szEntryPoint,
                                  LPCSTR szShaderModel,
                                  ID3DBlob** ppBlobOut);

private:
    void AwakeCheckVaildFile(const std::wstring& file);
};

} // namespace graphics