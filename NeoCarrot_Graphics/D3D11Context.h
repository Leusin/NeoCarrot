/// D3D11Context.h : d3d11 객체를  관리하는 객체 입니다.
/// 
/// 2023-12-27
///

#pragma once

#include <wrl.h>
#include <memory>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

struct D3D11_VIEWPORT;

namespace grahics
{
	class D3D11Context
	{
	public:
		D3D11Context(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
		~D3D11Context();

		ID3D11Device* Divice();
		ID3D11DeviceContext* DiviceContext();
		IDXGISwapChain* SwapChain();
		ID3D11Texture2D* DethStencilBuffer();
		ID3D11RenderTargetView* RenderTargetView();
		ID3D11DepthStencilView* DepthStencilView();

		// 랜더타깃 재설정
		void OnResize(int w, int h); 
		void BeginRender();
		void EndRender();

	private:
		void CreateDeviceContext();
		void CreateSwapChain(HWND hWnd, int w, int h);

		Microsoft::WRL::ComPtr<ID3D11Device> _d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dDiviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;

		D3D11_VIEWPORT* _screenViewport{ nullptr };

		UINT _4xMsaaQuality{};
	};
}