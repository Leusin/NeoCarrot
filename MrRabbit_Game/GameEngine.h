/// GameProcess.cpp : ������ �帧�� ���� �� �����մϴ�.
/// ��κ� �Ŵ��� Ŭ�������� ���⼭ ������ �ֽ��ϴ�.
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
		// ������ ����
		WindowInfomation* _windowInfo;

		// �Ŵ���
		std::unique_ptr<ManagerCreator> _managerCreator;
		std::vector<std::unique_ptr<IManager>> _managers;

		// �׷��� ����
		std::unique_ptr<ge::GraphicsEngine> _graphicsEngine{ nullptr };
	};

} // GameEngene