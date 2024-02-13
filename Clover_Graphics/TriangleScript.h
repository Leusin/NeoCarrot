#pragma once

#include "GetEntity.h"
#include "IComponent.h"

#include <wrl.h>
#include <d3dcompiler.h>
#include <d3d11.h>

namespace graphics
{

// 전방 선언
class D3Devices;

// 본문
class TriangleScript : public core::IComponent, virtual core::GetEntity
{

public:
    TriangleScript(EntityPtr entityPtr);

    void Awake() override;
    void Update(float dt) override;

private:
    D3Devices* _d3devices{nullptr};

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11PixelShader>  _pixelShader{nullptr};
    Microsoft::WRL::ComPtr<ID3D11InputLayout>  _vertexLayout{nullptr};
    Microsoft::WRL::ComPtr<ID3D11Buffer>       _vertexBuffer{nullptr};
    //Microsoft::WRL::ComPtr<ID3D11Buffer>       _indexBuffer{nullptr};
    //Microsoft::WRL::ComPtr<ID3D11Buffer>       _constantBuffer{nullptr};

    HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
};

} // namespace graphics