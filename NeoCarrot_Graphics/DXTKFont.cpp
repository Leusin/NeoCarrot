#include "DXTKFont.h"
#include <SimpleMath.h>
#include <tchar.h>

// ���� ��ΰ� ����� Ȯ���ϱ� ����
#if defined(DEBUG) || defined(_DEBUG)
#include <iostream>
#include <filesystem>
#endif


graphics::DXTKFont::DXTKFont(ID3D11Device* device, ID3D11DeviceContext* deviceCtext, ID3D11RasterizerState* rasterizerState, ID3D11DepthStencilState* dethsencil, FontType fontT)
	: _spriteBatch(std::make_unique<DirectX::SpriteBatch>(deviceCtext)), 
	_rasterizerState(rasterizerState)
	, _depthStencilState(dethsencil)
{
	const TCHAR* pathName =  L"../NeoCarrot_Graphics/Font";

	TCHAR* fileName{ nullptr };
	switch (fontT)
	{
	case FontType::Consolas:
		fileName = (TCHAR*)L"Consolas10.spritefont";
		break;
	case FontType::gulima9k:
		fileName = (TCHAR*)L"gulim9k.spritefont";
		break;
	case FontType::SegoeUI_:
		fileName = (TCHAR*)L"SegoeUI_18.spritefont";
		break;
	default:
		assert(false);
		break;
	}

	assert(fileName);

	std::wstring fullPath = std::wstring(pathName) + L"\\" + fileName;
	_spriteFont = std::make_unique<DirectX::SpriteFont>(device, fullPath.c_str());

	assert(_spriteFont);

	_spriteFont->SetLineSpacing(14.0f);

    // ���� ��ΰ� ����� Ȯ��
#if defined(DEBUG) || defined(_DEBUG)
    //std::cout << "( Font ) ���� ���: " << std::filesystem::current_path() << std::endl;
    std::cout << "\tDXTKFont Constructed\n";
#endif
}

#if defined(DEBUG) || defined(_DEBUG)
void graphics::DXTKFont::DrawTest()
{
	_spriteBatch->Begin();
	const wchar_t* text = L"�ٶ����� ���¹����� Ÿ����\n�䳢�� ��ī�� �� ������«�� ���ϼ̴�";
	_spriteFont->DrawString(_spriteBatch.get(), text, DirectX::XMFLOAT2(32.f, 36.f));
	_spriteBatch->End();
}
#endif

void graphics::DXTKFont::TextColor()
{
}

void graphics::DXTKFont::DrawTextColor(int x, int y, DirectX::XMFLOAT4 color, TCHAR* text, ...)
{
    TCHAR   _buffer[1024] = L"";
    va_list vl;
    va_start(vl, text);
    _vstprintf(_buffer, 1024, text, vl);
    va_end(vl);

    // SpriteBatch�� ���� ���� ������Ʈ�� ������ �� �ִ�.
    // ������, �׳� Begin�� �ϸ� �������Ľǹ��� �ɼ��� D3D11_DEPTH_WRITE_MASK_ZERO�� �Ǵ� ��. DSS�� �ٷ��� �ʴ� ���ݿ��� ������ �� �� �ִ�.
    // �Ʒ�ó�� ���⿡ �ɼ��� ALL�� �־��༭ ZERO�� �Ǵ� ���� ���� ���� �ְ�, �ٸ� �� ������Ʈ�� �׸� �� ����������Ʈ�� ���� �� �� ���� �ִ�.
    // DX12���� ����������Ʈ���� �׷��� �������� �͵� ���ش� ����. ���� ���� �ȵ������..
    //_spriteBatch->Begin(DirectX::SpriteSortMode::SpriteSortMode_Deferred, nullptr, nullptr, _depthStencilState/*, m_RasterizerState*/);
    _spriteBatch->Begin();
    _spriteFont->DrawString(_spriteBatch.get(),
                            _buffer,
                            DirectX::XMFLOAT2((float)x, (float)y),
                            DirectX::SimpleMath::Vector4(color));
    _spriteBatch->End();
}

void graphics::DXTKFont::DrawTextColor(int x, int y, const DirectX::XMVECTORF32& xmVector, TCHAR* text, ...)
{
    TCHAR   _buffer[1024] = L"";
    va_list vl;
    va_start(vl, text);
    _vstprintf(_buffer, 1024, text, vl);
    va_end(vl);

    DirectX::SimpleMath::Vector4 color;

    color.x = DirectX::XMVectorGetX(xmVector);
    color.y = DirectX::XMVectorGetY(xmVector);
    color.z = DirectX::XMVectorGetZ(xmVector);
    color.w = DirectX::XMVectorGetW(xmVector);

    _spriteBatch->Begin();
    _spriteFont->DrawString(_spriteBatch.get(),
                            _buffer,
                            DirectX::XMFLOAT2((float)x, (float)y),
                            DirectX::SimpleMath::Vector4(color));
    _spriteBatch->End();
}
