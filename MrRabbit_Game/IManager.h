/// IManager.h : �Ŵ��� ��ü���� ������ ������ ���� �������̽� Ŭ���� �Դϴ�.
/// 
/// 2023-12-26
/// 


#pragma once

namespace ge
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