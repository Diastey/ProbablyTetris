#pragma once
#include <stack>
#include "BaseScene.h"

class SceneStackManager
{
	static SceneStackManager* instance;

	std::stack<BaseScene*> sceneStack;

public:
	SceneStackManager() = default;
	~SceneStackManager();
	static SceneStackManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SceneStackManager();
		}
		return instance;
	}

	void PushScene(BaseScene* scene);
	void PopScene();
	void RunCurrentScene();
	void UpdateSceneStack(SceneUpdateResult result);
	void CloseGame();
	bool IsEmpty();
	static void DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
};

