/// D3D11Context.h : d3d11 ��ü��  �����ϴ� ��ü �Դϴ�.
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

namespace graphics
{
	class D3D11Context
	{
	public:
		D3D11Context(HINSTANCE hinst, HWND hWnd, int clientWidth, int clientHeight);
		~D3D11Context();

		ID3D11Device* Divice();
		ID3D11DeviceContext* DiviceContext();
		//IDXGISwapChain* SwapChain();
		//ID3D11Texture2D* DethStencilBuffer();
		//ID3D11RenderTargetView* RenderTargetView();
		//ID3D11DepthStencilView* DepthStencilView();

		// ����Ÿ�� �缳��
		void OnResize(int w, int h); 
		void BeginRender();
		void EndRender();

	private:
		void CreateDeviceContext();
		void CreateSwapChain(HWND hWnd, int w, int h);

		// ����̽�
		Microsoft::WRL::ComPtr<ID3D11Device> _d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dDiviceContext;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;

		// ���ҽ� ��
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;

		D3D11_VIEWPORT* _screenViewport{ nullptr };

		UINT _4xMsaaQuality{};
	};
}

//
// Direct3D 11 ����̽�
// 
//    ����̽�
//       ���ҽ� ������ ���÷��� ��� ��� ������ ���.
//       �ϳ��� �������α׷��� ��� �ϳ��� ����̽��� ������ �Ϲ������� �ϳ��� ����.
//       D3D11CreateDevice �Ǵ� D3D11CreateDviceAndSwapChain �Լ��� ������ �� �ְ�
//       D3D_DRIVER_TYPE �� ���� ����̹� Ÿ�� ������ �Ѵ�.
// 
//    ����̽� ���ؽ�Ʈ
//       ����̽��� ���� ȯ�� ����, ���������� ����, ������ ������ ���´�.
//       immediate ���ؽ�Ʈ�� deferred ���ؽ�Ʈ �� ���� ������ ����.
//       �� �� D3D11CreateDevice �Ǵ� D3D11CreateDviceAndSwapChain �Լ��� ���� �� �ִ�.
// 
// Direct3D 11 ���ҽ�
// 
//     ���ҽ� ���� ����
// 
// ID3D11DepthStencilView
// ID3D11RenderTargetView
// ID3D11ShaderResourceView
// ID3D11UnorderedAccessView	
// 
// 2024-01-14