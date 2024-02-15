#include "CompileShader.h"

#include <fstream>
#include <wrl.h>

#include <cassert>

namespace graphics
{

HRESULT CompileShader::CompileShaderFromFile(const WCHAR* szFileName,
                                             LPCSTR szEntryPoint,
                                             LPCSTR szShaderModel,
                                             ID3DBlob** ppBlobOut)
{
    CheckVaildFile(szFileName);

    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still
    // allows the shaders to be optimized and to run exactly the way they will
    // run in the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    Microsoft::WRL::ComPtr<ID3DBlob> pErrorBlob = nullptr;
    hr                                          = D3DCompileFromFile(szFileName,
                            nullptr,
                            nullptr,
                            szEntryPoint,
                            szShaderModel,
                            dwShaderFlags,
                            0,
                            ppBlobOut,
                            &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(
                reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
        }
        return hr;
    }

    return S_OK;
}

void CompileShader::CheckVaildFile(const std::wstring& file)
{
    std::ifstream fxhFin(file, std::ios::binary);

    if (!fxhFin)
    {
        MessageBox(0, L"파일을 찾을 수 없습니다.", 0, 0);
    }

    assert(fxhFin);
}

} // namespace graphics