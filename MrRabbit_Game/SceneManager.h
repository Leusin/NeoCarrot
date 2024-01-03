/// SceneManager.h : ���� �����ϴ� �޴��� �Դϴ�.
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