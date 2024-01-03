/// Application.h : ���� ���� ��ü�� ������ ȣ���մϴ�.
/// WINDOW API ���� ��ü�� �ʱ�ȭ �� �����մϴ�.
/// 
/// 2023-12-22
///


#pragma once

#include <windows.h>
#include <memory>

#include "WindowInfomation.h"

namespace ge 
{ 
	class GameEngine; 
	struct WindowInfomation;
}

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

	ge::WindowInfomation _winInfo;
	std::unique_ptr<ge::GameEngine>_gameEngine{ nullptr };
};