/// IManagerFactory.h: 매니저 클래스를 만들어내는 Creator 클래스 입니다.
/// 
/// 추상 매서드 패턴을 이용해 여러가지 클래스를 반환합니다.
/// 전달 받은 인자에 따라 반환하는 매니저 클래스의 종류가 다릅니다.
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
		/// 메니저를 만들어 반환하는 팩토리 매서드
		/// </summary>
		/// <param name="mt">매니저 타입 enum 클래스</param>
		/// <returns>IManager 의 하위 클래스</returns>
		std::unique_ptr<IManager> CreateManager(ManagerType&& managerType);
	};

} // GameEngine