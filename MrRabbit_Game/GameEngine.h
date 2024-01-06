/// GameProcess.cpp : ������ �帧�� ���� �� �����մϴ�.
/// ��κ� �Ŵ��� Ŭ�������� ���⿡ �ֽ��ϴ�.
/// 
/// 2023-12-22


#pragma once

#define E_TEST

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

#pragma region Manager

		std::unique_ptr<ManagerCreator> _managerCreator;
		std::vector<std::unique_ptr<IManager>> _managers;

#pragma endregion Manager

		// �׷��� ����
		std::unique_ptr<grahics::GraphicsEngine> _graphicsEngine{ nullptr };
	};

} // GameEngene