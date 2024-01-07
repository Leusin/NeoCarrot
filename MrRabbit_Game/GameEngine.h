/// GameProcess.cpp : ������ �帧�� ���� �� �����մϴ�.
/// ��κ� �Ŵ��� Ŭ�������� ���⿡ �ֽ��ϴ�.
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
    class TimeManager;
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
		// ������ ����. 
		// �ʱ�ȭ ��  MassageProc���� ����Ѵ�.
		WindowInfomation* _windowInfo;

		std::unique_ptr<SceneManager> _sceneManager;
        std::unique_ptr<TimeManager>  _timeManager;

		// �׷��� ����
		std::unique_ptr<grahics::GraphicsEngine> _graphicsEngine{ nullptr };
	};

} // GameEngene