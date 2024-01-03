/// Font.h : 하나의 텍스트를 출력할 수 있도록 돕는 클래스 입니다.
/// 
/// 2023-12-27
/// 


#pragma once

#include "FontType.h"
#include <memory>
#include <SpriteFont.h>
#include <SpriteBatch.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RasterizerState;
struct ID3D11DepthStencilState;


namespace ge
{
	class Font
	{
	public:
		Font(ID3D11Device* device
			, ID3D11DeviceContext* deviceCtext
			, ID3D11RasterizerState* rasterizerState
			, ID3D11DepthStencilState* ds
			, FontType ft);

#if defined(DEBUG) || defined(_DEBUG)
		void DrawTest();
#endif
		void TextColor();

	private:
		std::unique_ptr<DirectX::SpriteBatch> _spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> _spriteFont;

		// 그냥 사용하면 뎁스 문제가 생긴다.
		ID3D11RasterizerState* _rasterizerState{ nullptr };
		ID3D11DepthStencilState* _depthStencilState{ nullptr };
	};
}