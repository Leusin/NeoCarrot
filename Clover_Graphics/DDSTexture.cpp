#include "DDSTexture.h"

#include "DDSTextureLoader.h"

namespace graphics
{

DDSTexture::DDSTexture()
{
}

DDSTexture::DDSTexture(const DDSTexture&)
{
}

DDSTexture::~DDSTexture()
{
}

void DDSTexture::Initialize(ID3D11Device* device,
    ID3D11DeviceContext* deviceContext,
    const WCHAR* fileNmae)
{
    // 셰이더 리소스뷰를 생성하고, 
    // device context 을 추가하면 밉맵 자동 생성
    DirectX::CreateDDSTextureFromFile(device
        , deviceContext
        , fileNmae
        , _texture.GetAddressOf()
        , _textureView.GetAddressOf()
        /*,  0, nullptr*/);

}

ID3D11ShaderResourceView* DDSTexture::GetTexture()
{
    return _textureView.Get();
}

} // namespace graphics