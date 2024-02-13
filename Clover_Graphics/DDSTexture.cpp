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
    // ���̴� ���ҽ��並 �����ϰ�, 
    // device context �� �߰��ϸ� �Ӹ� �ڵ� ����
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