#include "TriangleScript.h"

#include "D3Devices.h"
#include "components.h"
#include "InputLayouts.h"

#include <fstream>
#include <memory>
#include <vector>

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
TriangleScript::TriangleScript(EntityPtr entityPtr) :
GetEntity(EntityPtr(entityPtr)),
_d3devices{GetComponent<graphics::D3Devices>()}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd TriangleScript Component\n";
#endif // _DEBUG;
}

void TriangleScript::Awake()
{
    HRESULT hr = S_OK;

    std::wstring _fxhFilename = L"../NeoCarrot_Graphics/HLSL/triangle.fxh";
    std::wstring _vsFilename  = L"../NeoCarrot_Graphics/HLSL/triangle_vs.hlsl";
    std::wstring _psFilename  = L"../NeoCarrot_Graphics/HLSL/triangle_ps.hlsl";

    { // AwakeCheckFile
        std::ifstream fxhFin(_fxhFilename, std::ios::binary);
        std::ifstream vsFin(_vsFilename, std::ios::binary);
        std::ifstream psFin(_psFilename, std::ios::binary);

        if (!fxhFin || !vsFin || !psFin)
        {

            MessageBox(0, L"������ ã�� �� ������", 0, 0);
        }

        assert(fxhFin || vsFin || psFin);
    }

    auto* device        = _d3devices->GetDevice();
    auto* deviceContext = _d3devices->GetDeviceContext();

    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{nullptr};

    //
    // CreateShaders
    //
    {
        { // AwakeCompileShader

            hr = CompileShaderFromFile(_fxhFilename.c_str(), "VS", "vs_5_0", pVSBlob.GetAddressOf());

            if (FAILED(hr))
            {
                std::cout << "\t\t\t\t���̴��� ������ �ȵ� --- !\n";
            }

            assert(pVSBlob.Get());
        }

        { // AwakeCreateVertexShader
            hr = device->CreateVertexShader(pVSBlob->GetBufferPointer(),
                                            pVSBlob->GetBufferSize(),
                                            nullptr,
                                            _vertexShader.GetAddressOf());
            if (FAILED(hr))
            {
                std::cout << "\t\t\t\t���ؽ� ���̴��� ���� �ȵ� --- !\n";
            }

            assert(_vertexShader.Get());
        }
    }

    { // AwakeCreateInputLayout

        //
        // D3D11_INPUT_ELEMENT_DESC ����ü ����.
        // 
        // static const std::vector<D3D11_INPUT_ELEMENT_DESC> posDesc = {
        // {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        // };
        //
        // �ø�ƽ ���� / �ø�ƽ �ε��� / ���� / ��ǲ���� / ������ / ��ǲ ���� Ŭ���� / �ν��Ͻ� ������ ���� ����Ʈ
        // 
        // �ø�ƽ ����
        //    ��ҹ��ڸ� �������� �ʽ��ϴ�.
        // 
        // �ø�ƽ ���� �ε���
        //     "COLOR0" �� "COLOR1"�� ���� ���ڰ� �߰��� �ø�ƽ �̸��� ����ϴ� ���, 
        //     �� ��Ҵ� ���� �ٸ� �ø�ƽ �ε��� 0�� 1�� ����Ͽ� ���� �ø�ƽ �̸��� "COLOR"�� ������ �� �ֽ��ϴ�.
        // 
        // ������ �ڼ��� ������
        //    https://learn.microsoft.com/en-us/previous-versions//ff729719(v=vs.85)?redirectedfrom=MSDN
        //

        hr = device->CreateInputLayout(posDesc.data(),
                                       static_cast<UINT>(posDesc.size()),
                                       pVSBlob->GetBufferPointer(),
                                       pVSBlob->GetBufferSize(),
                                       _vertexLayout.GetAddressOf());

        if (FAILED(hr))
        {
            std::cout << "\t\t\t\t���ؽ� ���̾ƿ��� ���� �ȵ� --- !\n";
        }

        assert(_vertexLayout.Get());

    }

    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{nullptr};

    { // AwakeCompilePixelShader

        hr = CompileShaderFromFile(_fxhFilename.c_str(), "PS", "ps_5_0", pPSBlob.GetAddressOf());

        if (FAILED(hr))
        {
            std::cout << "\t\t\t\t�ȼ� ���̴��� ������ �ȵ� --- !\n";
        }

        assert(pPSBlob.Get());
    }

    { // AwakeCreatePixelShader

        hr = device->CreatePixelShader(pPSBlob->GetBufferPointer(),
                                       pPSBlob->GetBufferSize(),
                                       nullptr,
                                       _pixelShader.GetAddressOf());

        if (FAILED(hr))
        {
            std::cout << "\t\t\t\t�ȼ� ���̴��� ���� �ȵ� --- !\n";
        }

        assert(_pixelShader.Get());
    }

    { // AwakeCreateVertexBuffer

        std::vector<Pos> vertices = {
            {DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f)},
            {DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f)},
            {DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)},
        };
        D3D11_BUFFER_DESC bd = {};
        bd.Usage             = D3D11_USAGE_DEFAULT;
        bd.ByteWidth         = sizeof(Pos) * 3;
        bd.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags    = 0;

        D3D11_SUBRESOURCE_DATA InitData = {};
        InitData.pSysMem                = vertices.data();
        hr                              = device->CreateBuffer(&bd, &InitData, _vertexBuffer.GetAddressOf());

        assert(_vertexBuffer.Get());
    }
}

void TriangleScript::Update(float dt)
{
    auto* deviceContext = _d3devices->GetDeviceContext();
    
    deviceContext->IASetInputLayout(_vertexLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 

    { // UpdateSetVertexBuffer
        UINT stride = sizeof(Pos);
        UINT offset = 0;
        deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
    }
    
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
    deviceContext->Draw(3, 0);
}

HRESULT TriangleScript::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows
    // the shaders to be optimized and to run exactly the way they will run in
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    Microsoft::WRL::ComPtr <ID3DBlob> pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
        }
        return hr;
    }

    return S_OK;
}

} // namespace graphics
