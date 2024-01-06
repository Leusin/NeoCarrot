/// ManagerType.h: �Ŵ��� Ŭ������ ������ �����մϴ�.
/// GameEngine Ŭ������ IManagerFactory Ŭ������ ����մϴ�.
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