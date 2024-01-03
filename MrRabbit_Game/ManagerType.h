/// ManagerType.h: 매니저 클래스의 종류를 정의합니다.
/// GameEngine 클래스와 IManagerFactory 클래스에 사용합니다.
/// 
/// 2023-12-26
/// 


#pragma once

namespace ge
{
	enum class ManagerType
	{
		Scene,
		Resource,
		Input,
		Entity,
		Audio,
		Event,
		Time,
		UI
	};

}// GameEngine