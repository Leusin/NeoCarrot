/// WinMain.cpp : 프로그램 실행이 시작되고 종료됩니다.
/// 
/// 2023-12-22

// 디버그일 떄 위한 콘솔 창 생성
#if defined(DEBUG) || defined(_DEBUG)

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 라이브러리
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 헤더
#include <windows.h>
#include "Application.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE prevInstance, 
	_In_ PSTR cmdLine, 
	_In_ int showCmd)
{
#if defined(DEBUG) | defined(_DEBUG)

	// 런타임 메모리 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif

	Application* application = new Application(hInstance);
	
	application->Initialize();
	application->Process();
	application->Finalize();
	
	delete application;
    application = nullptr;

	return 0;
}
