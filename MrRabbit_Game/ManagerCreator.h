/// IManagerFactory.h: �Ŵ��� Ŭ������ ������ Creator Ŭ���� �Դϴ�.
/// 
/// �߻� �ż��� ������ �̿��� �������� Ŭ������ ��ȯ�մϴ�.
/// ���� ���� ���ڿ� ���� ��ȯ�ϴ� �Ŵ��� Ŭ������ ������ �ٸ��ϴ�.
/// 
/// 2023-12-26
///


#pragma once

#include "ManagerType.h"

#include <memory>

namespace game
{
	class IManager;

	class ManagerCreator
	{
	public:
		ManagerCreator() {};
		virtual ~ManagerCreator() {}

		/// <summary>
		/// �޴����� ����� ��ȯ�ϴ� ���丮 �ż���
		/// </summary>
		/// <param name="mt">�Ŵ��� Ÿ�� enum Ŭ����</param>
		/// <returns>IManager �� ���� Ŭ����</returns>
		std::unique_ptr<IManager> CreateManager(ManagerType&& managerType);
	};

} // GameEngine