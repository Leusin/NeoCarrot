/// WindowInfomation.h: �� ������Ʈ(Demo, Game)�� ���������� ������ �ϴ� �����͸� �����մϴ�.
/// 
/// 2023-12-22


#pragma once

#include <windows.h>

namespace data
{
	struct WindowInfo
	{
		HINSTANCE hInstance{ nullptr };
		HWND hMainWnd/*{ nullptr }*/;

		LONG clienLeft{ 0 };
		LONG clienTop{ 0 };
		LONG clientWidth{ 800 };
		LONG clientHeight{ 600 };

		const wchar_t* mainWndclassName{ L"NeoCarrot" };
		const wchar_t* mainWndCaption{ L"����� �����ּ���" };
	};
}