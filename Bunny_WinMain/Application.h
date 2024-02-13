/// Application.h : ���� ���� ��ü�� ������ ȣ���մϴ�.
/// WINDOW API ���� ��ü�� �ʱ�ȭ �� �����մϴ�.
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