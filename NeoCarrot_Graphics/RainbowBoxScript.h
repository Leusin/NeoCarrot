#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

namespace graphics
{

// 전방 선언
class D3Devices;

// 본문
class RainbowBoxScript : public core::IComponent, virtual core::GetEntity
{

public:
    RainbowBoxScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
    void AwakeCheckVaildFile(const std::wstring& file);

    // BindVSResource
    // BindPSResource

    // SetVSArgument
    // SetPSArgument

    // BindWVPMatrix
    // BindLight
    // BindBone

private:
    D3Devices* _d3devices{nullptr};

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  _pixelShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  _vertexLayout{nullptr};
    Microsoft::WRL::ComPtr<ID3D11Buffer>       _vertexBuffer{nullptr};
    Microsoft::WRL::ComPtr<ID3D11Buffer>       _indexBuffer{nullptr};
    Microsoft::WRL::ComPtr<ID3D11Buffer>       _constantBuffer{nullptr};
};

} // namespace graphics