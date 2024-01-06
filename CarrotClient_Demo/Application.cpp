#include "Application.h"
#include "GameEngine.h"
#include "resource.h"

namespace
{
	// 전역 창에서 Window 메시지를 전달하는데 사용한다.
	Application* app{ nullptr };
}

LRESULT CALLBACK 
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return app->GetWinMssageProc(hwnd, msg, wParam, lParam);
}

Application::Application(const HINSTANCE& hIns)
{
	_winInfo.hInstance = hIns;
	_gameEngine = std::make_unique<game::GameEngine>(&_winInfo);
	app = this;
	InitalizeMainWindow();

}

Application::~Application()
{
}

void Application::Initialize()
{
	_gameEngine->Initialize();
}

void Application::Process()
{
	_gameEngine->Process();
}

void Application::Finalize()
{
	_gameEngine->Finalize();
}

LRESULT CALLBACK  Application::GetWinMssageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return _gameEngine->MessageProc(hwnd, msg, wParam, lParam);;
}

void Application::InitalizeMainWindow()
{
	WNDCLASS windowClass = { 0, };
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = MainWndProc;											// 윈도우 프로시저
	windowClass.cbClsExtra = 0;														// 클래스 여분 메모리
	windowClass.cbWndExtra = 0;														// 윈도우 여분 메모리
	windowClass.hInstance = _winInfo.hInstance;										// 인스턴스
	windowClass.hIcon = LoadIcon(_winInfo.hInstance, MAKEINTRESOURCE(IDI_ICON1));	// 아이콘
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);									// 커서
	windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);				// 백그라운드
	windowClass.lpszMenuName = 0;													// 메뉴 이름
	windowClass.lpszClassName = _winInfo.mainWndclassName;							// 클래스 이름

	if (!RegisterClass(&windowClass))
	{
		MessageBox(0, L"RegisterClass 호출 실패.", 0, 0);
		return;
	}

	RECT cilentPositionAndSize = { _winInfo.clienLeft, _winInfo.clienTop, _winInfo.clientWidth, _winInfo.clientHeight };

	AdjustWindowRect(&cilentPositionAndSize, WS_OVERLAPPEDWINDOW, false);
	int width = cilentPositionAndSize.right - cilentPositionAndSize.left;
	int height = cilentPositionAndSize.bottom - cilentPositionAndSize.top;
	
	_winInfo.hMainWnd = CreateWindow(_winInfo.mainWndclassName, _winInfo.mainWndCaption, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, _winInfo.hInstance, 0);

	if (!_winInfo.hMainWnd)
	{
		MessageBox(0, L"CreateWindow 함수 호출 실패.", 0, 0);
		return;
	}
	
	ShowWindow(_winInfo.hMainWnd, SW_SHOW);
	UpdateWindow(_winInfo.hMainWnd);
}