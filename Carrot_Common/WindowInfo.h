/// WindowInfomation.h: 두 프로젝트(Demo, Game)가 공동적으로 가져야 하는 데이터를 정의합니다.
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
		const wchar_t* mainWndCaption{ L"당근을 흔들어주세요" };
	};
}