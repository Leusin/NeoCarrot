/// SceneManager.h : 씬을 관리하는 메니저 입니다.
/// 
/// 2023-12-26
/// 


#pragma once
#include "IManager.h"

namespace ge
{
	class IScene;

class SceneManager : public IManager
{
public:
	SceneManager();
	~SceneManager();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

private:
	IScene* _nowScene{ nullptr };
};

} // GameEngine