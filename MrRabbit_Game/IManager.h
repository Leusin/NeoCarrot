/// IManager.h : 매니저 객체들의 다형적 동작을 위한 인터페이스 클래스 입니다.
/// 
/// 2023-12-26
/// 


#pragma once

namespace game
{
	class IManager
	{
	public:
		virtual ~IManager() {};

		virtual void Initialize() abstract;
		virtual void Update() abstract;
		virtual void Finalize() abstract;
	};

} // GameEngine