/// Font.h : �ϳ��� �ؽ�Ʈ�� ����� �� �ֵ��� ���� Ŭ���� �Դϴ�.
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


namespace graphics
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
        void DrawTextColor(int x, int y, DirectX::XMFLOAT4 color, TCHAR* text, ...);
        void DrawTextColor(int x, int y, const DirectX::XMVECTORF32& xmVector, TCHAR* text, ...);

	private:
		std::unique_ptr<DirectX::SpriteBatch> _spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> _spriteFont;

		// �׳� ����ϸ� ���� ������ �����.
		ID3D11RasterizerState* _rasterizerState{ nullptr };
		ID3D11DepthStencilState* _depthStencilState{ nullptr };
	};
}