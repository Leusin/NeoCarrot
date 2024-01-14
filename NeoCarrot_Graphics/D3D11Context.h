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

		// 랜더타깃 재설정
		void OnResize(int w, int h); 
		void BeginRender();
		void EndRender();

	private:
		void CreateDeviceContext();
		void CreateSwapChain(HWND hWnd, int w, int h);

		// 디바이스
		Microsoft::WRL::ComPtr<ID3D11Device> _d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dDiviceContext;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;

		// 리소스 뷰
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;

		D3D11_VIEWPORT* _screenViewport{ nullptr };

		UINT _4xMsaaQuality{};
	};
}

//
// Direct3D 11 디바이스
// 
//    디바이스
//       리소스 생성과 디스플레이 어뎁터 기능 나열에 사용.
//       하나의 응용프로그램은 적어도 하나의 디바이스를 가지고 일반적으로 하나만 생성.
//       D3D11CreateDevice 또는 D3D11CreateDviceAndSwapChain 함수로 생성할 수 있고
//       D3D_DRIVER_TYPE 로 각종 드라이버 타입 설정을 한다.
// 
//    디바이스 컨텍스트
//       디바이스에 대한 환경 설정, 파이프라인 설정, 랜더링 역할을 갖는다.
//       immediate 컨텍스트와 deferred 컨텍스트 두 가지 종류가 있음.
//       둘 다 D3D11CreateDevice 또는 D3D11CreateDviceAndSwapChain 함수로 만들 수 있다.
// 
// Direct3D 11 리소스
// 
//     리소스 뷰의 종류
// 
// ID3D11DepthStencilView
// ID3D11RenderTargetView
// ID3D11ShaderResourceView
// ID3D11UnorderedAccessView	
// 
// 2024-01-14