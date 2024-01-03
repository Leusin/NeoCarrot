/// GameProcess.cpp : 게임의 흐름을 제어 및 관리합니다.
/// 대부분 매니저 클래스들을 여기서 가지고 있습니다.
/// 
/// 2023-12-22
///


#pragma once

#include "IManager.h"
#include "ManagerCreator.h"

#include <windows.h>
#include <vector>
#include <memory>

namespace ge { class GraphicsEngine; }

namespace ge
{
	class IManger;
	class ManagerCreator;
	struct WindowInfomation;

	class GameEngine
	{
	public:
		GameEngine(WindowInfomation* winInfo);
		~GameEngine();

		void Initialize();
		void Process();
		void Finalize();
		
		LRESULT MessageProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		// 윈도우 정보
		WindowInfomation* _windowInfo;

		// 매니저
		std::unique_ptr<ManagerCreator> _managerCreator;
		std::vector<std::unique_ptr<IManager>> _managers;

		// 그래픽 엔진
		std::unique_ptr<ge::GraphicsEngine> _graphicsEngine{ nullptr };
	};

} // GameEngene