#include "RainbowBoxScript.h"

#include "D3Devices.h"
#include "components.h"

#include <fstream>
#include <memory>
#include <vector>

#include <cassert>
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

namespace graphics
{
RainbowBoxScript::RainbowBoxScript(EntityPtr entityPtr) 
    : GetEntity(EntityPtr(entityPtr))
    , _d3devices{GetComponent<graphics::D3Devices>()}
{
#ifdef _DEBUG
    std::cout << "\t\t\t\tAdd RainbowBoxScript Component\n";
#endif // _DEBUG;
}

void RainbowBoxScript::Awake()
{
    HRESULT hr = S_OK;

    std::wstring fxhFilename = L"../NeoCarrot_Graphics/HLSL/rainbowbox.hlsl";

    AwakeCheckVaildFile(fxhFilename);

    auto* device        = _d3devices->GetDevice();
    auto* deviceContext = _d3devices->GetDeviceContext();

    Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob{nullptr};

    // 
    // CreateVertexShader
    //

    {
        { // AwakeCompileShader

            hr = CompileShaderFromFile(fxhFilename.c_str(), "VS", "vs_5_0", pVSBlob.GetAddressOf());

            if (FAILED(hr))
            {
                std::cout << "\t\t\t\t¼ÎÀÌ´õ°¡ ÄÄÆÄÀÏ ¾ÈµÊ --- !\n";
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
                std::cout << "\t\t\t\t¹öÅØ½º ¼ÎÀÌ´õ°¡ »ý¼º ¾ÈµÊ --- !\n";
            }

            assert(_vertexShader.Get());
        }
    }   

    //
    // CreateInputLayout
    //

    { // AwakeCreateInputLayout

       

        hr = device->CreateInputLayout(PosColorDesc.data(),
                                           static_cast<unsigned int>(PosColorDesc.size()),
                                       pVSBlob->GetBufferPointer(),
                                       pVSBlob->GetBufferSize(),
                                       _vertexLayout.GetAddressOf());

        if (FAILED(hr))
        {
            std::cout << "\t\t\t\t¹öÅØ½º ·¹ÀÌ¾Æ¿ôÀÌ »ý¼º ¾ÈµÊ --- !\n";
        }

        assert(_vertexLayout.Get());
    }

    Microsoft::WRL::ComPtr<ID3DBlob> pPSBlob{nullptr};

    //
    // CreatePixelShader
    //
    
    {
        { // AwakeCompilePixelShader

            hr = CompileShaderFromFile(fxhFilename.c_str(), "PS", "ps_5_0", pPSBlob.GetAddressOf());

            if (FAILED(hr))
            {
                std::cout << "\t\t\t\tÇÈ¼¿ ¼ÎÀÌ´õ°¡ ÄÄÆÄÀÏ ¾ÈµÊ --- !\n";
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
                std::cout << "\t\t\t\tÇÈ¼¿ ¼ÎÀÌ´õ°¡ »ý¼º ¾ÈµÊ --- !\n";
            }

            assert(_pixelShader.Get());
        }
    }

    //
    // CreateVertexBuffer
    //

    // AwakeCreateVertexBuffer

    std::vector<Pos> vertices = 
    {
        {DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f)},
        {DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f)},
        {DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
        {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f)},
        {DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f)},
        {DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f)},
        {DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f)},
        {DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f)}
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage             = D3D11_USAGE_DEFAULT;
    bd.ByteWidth         = sizeof(Pos) * 8;
    bd.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags    = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem                = vertices.data();
    hr                              = device->CreateBuffer(&bd, &InitData, _vertexBuffer.GetAddressOf());

    assert(_vertexBuffer.Get());

    //
    // CreateIndexBuffer
    //
    std::vector<WORD> indices =
    {
        3,1,0,
        2,1,3,

        0,5,4,
        1,5,0,

        3,4,7,
        0,4,3,

        1,6,5,
        2,6,1,

        2,7,6,
        3,7,2,

        6,4,5,
        7,4,6
    };

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36; // 36 vertices needed for 12 triangles in a triangle list
    bd.BindFlags      = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices.data();
    hr = device->CreateBuffer( &bd, &InitData, _indexBuffer.GetAddressOf() );
    
    //
    // AwakeCreateConstant buffer
    //
    bd.Usage          = D3D11_USAGE_DEFAULT;
    bd.ByteWidth      = sizeof(ConstantBuffer);
    bd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr                = device->CreateBuffer(&bd, nullptr, _constantBuffer.GetAddressOf());

}

void RainbowBoxScript::Update(float dt)
{
    auto* deviceContext = _d3devices->GetDeviceContext();

    //
    // UpdateInputAssemBler
    //
    deviceContext->IASetInputLayout(_vertexLayout.Get());

    UINT stride = sizeof(Pos);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);

    deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 

    //
    // Update variables
    //
    ConstantBuffer cb;
    auto* Trans = GetComponent<Transpose>();
    cb.WorldViewProj = XMMatrixTranspose(Trans->GetWorldViewProj());

    deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &cb, 0, 0);

    //
    // UpdateRender
    //
    deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
    deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
    deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
    deviceContext->DrawIndexed(36, 0, 0);
}

HRESULT RainbowBoxScript::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

void RainbowBoxScript::AwakeCheckVaildFile(const std::wstring& file)
{
    std::ifstream fxhFin(file, std::ios::binary);

    if (!fxhFin)
    {
        MessageBox(0, L"ÆÄÀÏÀ» Ã£À» ¼ö ¾øÀ¸¼¾", 0, 0);
    }

    assert(fxhFin);
}

} // namespace graphics
