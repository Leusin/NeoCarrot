#pragma once

#include <directxmath.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <wrl.h>
#include <memory>

namespace graphics
{

class DDSTexture 
{
public:
    DDSTexture();
    DDSTexture(const DDSTexture&);
    ~DDSTexture();

    void Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* fileNmae);

    ID3D11ShaderResourceView* GetTexture();

private:
   std::unique_ptr<unsigned char> _targaData{ nullptr };
   Microsoft::WRL::ComPtr<ID3D11Resource> _texture{ nullptr };
   Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _textureView{ nullptr };
};

} // namespace graphics