/// CompileShader.h : ���̴� ������ �Լ� ȣ���� �ʷ�� �ϴ� Ŭ�������� ���� Ŭ����.
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
/// ����ؼ� ����ϴ� ���� �ǵ��ϱ� ������ ���� �����ϴ� ���� ����
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