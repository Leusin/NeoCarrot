#include "DXTKFont.h"
#include <SimpleMath.h>
#include <tchar.h>

// 현재 경로가 어딘지 확인하기 위해
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

    // 현재 경로가 어딘지 확인
#if defined(DEBUG) || defined(_DEBUG)
    //std::cout << "( Font ) 파일 경로: " << std::filesystem::current_path() << std::endl;
    std::cout << "\tDXTKFont Constructed\n";
#endif
}

#if defined(DEBUG) || defined(_DEBUG)
void graphics::DXTKFont::DrawTest()
{
	_spriteBatch->Begin();
	const wchar_t* text = L"다람쥐썬더 헌쳇바퀴에 타고파\n토끼와 피카츄 또 바지락짬뽕 원하셨대";
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

    // SpriteBatch에 여러 렌더 스테이트를 지정할 수 있다.
    // 문제는, 그냥 Begin만 하면 뎁스스탠실버퍼 옵션이 D3D11_DEPTH_WRITE_MASK_ZERO가 되는 듯. DSS를 다루지 않는 포반에는 문제가 될 수 있다.
    // 아래처럼 여기에 옵션을 ALL로 넣어줘서 ZERO가 되는 것을 막을 수도 있고, 다른 쪽 오브젝트를 그릴 때 렌더스테이트를 지정 해 줄 수도 있다.
    // DX12에서 렌더스테이트등을 그렇게 가져가는 것도 이해는 간다. 별로 맘에 안들었겠지..
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
