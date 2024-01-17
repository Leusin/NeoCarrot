#include "Texture.h"

#include "Effect.h"
#include "DDSTextureLoader.h"

#include <directxmath.h>
#include <cassert>
#include <fstream>

namespace graphics
{

Texture::Texture(EntityPtr entityPtr, const std::wstring& filename)
: GetEntity(EntityPtr(entityPtr)),
    _d3device{GetComponent<graphics::D3Devices>()}
{

    std::ifstream fin(filename, std::ios::binary);

    if (!fin)
    {
        MessageBox(0, L" 텍스처 파일을 찾을 수 없으센.", 0, 0);
    }

    DirectX::XMStoreFloat4x4(&_texTransform, DirectX::XMMatrixIdentity());

    DirectX::CreateDDSTextureFromFile(_d3device->GetDevice(), filename.c_str(), nullptr, _diffuseMapSRV.GetAddressOf());

    assert(_diffuseMapSRV.Get() && "Texture 에서 초기화 안됨");
}
void Texture::Update(float dt)
{
    SetEffect();
}
void Texture::SetEffect()
{
    auto fx = GetComponent<Effect>();

    fx->SetTexTransform(XMLoadFloat4x4(&_texTransform));
    fx->SetDiffuseMap(_diffuseMapSRV.Get());
}
} // namespace graphics