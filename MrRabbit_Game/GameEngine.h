/// GameProcess.cpp : 게임의 흐름을 제어 및 관리합니다.
/// 대부분 매니저 클래스들을 여기에 있습니다.
/// 
/// 2023-12-22


#pragma once
#include "IManager.h"
#include "ManagerCreator.h"

#include <windows.h>
#include <vector>
#include <memory>

namespace grahics { class GraphicsEngine; }

namespace game
{
	class IManger;
	class ManagerCreator;
    class SceneManager;
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
		// 윈도우 정보. 
		// 초기화 및  MassageProc에서 사용한다.
		WindowInfomation* _windowInfo;

#pragma region Manager

		std::unique_ptr<ManagerCreator> _managerCreator;
		std::unique_ptr<SceneManager> _sceneManager;
		std::vector<std::unique_ptr<IManager>> _managers;

#pragma endregion Manager

		// 그래픽 엔진
		std::unique_ptr<grahics::GraphicsEngine> _graphicsEngine{ nullptr };
	};

} // GameEngene