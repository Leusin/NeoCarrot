#include "Font.h"

// 현재 경로가 어딘지 확인하기 위해
#if defined(DEBUG) || defined(_DEBUG)
#include <iostream>
#include <filesystem>
#endif


ge::Font::Font(ID3D11Device* device, ID3D11DeviceContext* deviceCtext, ID3D11RasterizerState* rasterizerState, ID3D11DepthStencilState* dethsencil, FontType fontT)
	: _spriteBatch(std::make_unique<DirectX::SpriteBatch>(deviceCtext)), 
	_rasterizerState(rasterizerState)
	, _depthStencilState(dethsencil)
{

// 현재 경로가 어딘지 확인 
#if defined(DEBUG) || defined(_DEBUG)
		std::cout << "Font.h\n\tFont.cpp 파일 경로: " << std::filesystem::current_path() << std::endl;
#endif

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
}

#if defined(DEBUG) || defined(_DEBUG)
void ge::Font::DrawTest()
{
	_spriteBatch->Begin();
	const wchar_t* text = L"다람쥐썬더 헌쳇바퀴에 타고파\n토끼와 피카츄 또 바지락짬뽕 원하셨대";
	_spriteFont->DrawString(_spriteBatch.get(), text, DirectX::XMFLOAT2(32.f, 36.f));
	_spriteBatch->End();
}
#endif

void ge::Font::TextColor()
{
}
