/// Font.h : �ϳ��� �ؽ�Ʈ�� ����� �� �ֵ��� ���� Ŭ���� �Դϴ�.
///
/// 2023-12-27


#pragma once

#include "FontType.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <memory>
#include <string>

namespace graphics
{
class Devices;
struct RenderStates;

class DXTKFont
{
public:
    DXTKFont(ID3D11Device*            device,
             ID3D11DeviceContext*     deviceCtext,
             ID3D11RasterizerState*   rasterizerState,
             ID3D11DepthStencilState* ds,
             FontType                 ft);

    DXTKFont(const Devices* devices, const RenderStates* renderStates, const FontType fontT);


#if defined(DEBUG) || defined(_DEBUG)
    void DrawTest();
#endif
    void TextColor();
    void DrawTextColor(int x, int y, DirectX::XMFLOAT4 color, TCHAR* text, ...);
    void DrawTextColor(int x, int y, const DirectX::XMVECTORF32& xmVector, TCHAR* text, ...);

private:
    const std::wstring GetFontFilePath(const FontType& fontT);

    std::unique_ptr<DirectX::SpriteBatch> _spriteBatch{nullptr};
    std::unique_ptr<DirectX::SpriteFont>  _spriteFont{nullptr};

    // �׳� ����ϸ� ���� ������ �����.
    ID3D11RasterizerState*   _rasterizerState{nullptr};
    ID3D11DepthStencilState* _depthStencilState{nullptr};
};
} // namespace graphics