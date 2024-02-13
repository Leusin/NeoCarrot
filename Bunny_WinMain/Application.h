/// Application.h : 게임 엔진 객체를 생성및 호출합니다.
/// WINDOW API 관련 객체를 초기화 및 실행합니다.
/// 
/// 2023-12-22


#pragma once

#include "WindowInfo.h"
#include "System.h"

#include <windows.h>
#include <memory>

class Application
{
public:
	Application(const HINSTANCE& hInstance);
	~Application();

	void Initialize();
	void Process();
	void Finalize();

	LRESULT CALLBACK  GetWinMssageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	void InitalizeMainWindow();

	data::WindowInfo                  _winInfo;
	std::unique_ptr<game::System> _gameSystem{ nullptr };
};