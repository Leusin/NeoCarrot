/// ManagerType.h: 매니저 클래스의 종류를 정의합니다.
/// GameEngine 클래스와 IManagerFactory 클래스에 사용합니다.
/// 
/// 2023-12-26
/// 


#pragma once

namespace game
{
	enum class ManagerType
	{
		Unknown = -1,
		Scene = 0,
		Resource,
		Input,
		Entity,
		Audio,
		Event,
		Time,
		UI,

		NumManager,
	};

}// GameEngine