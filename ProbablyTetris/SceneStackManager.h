#pragma once
#include <stack>
#include "BaseScene.h"

class SceneStackManager
{
	std::stack<BaseScene*> sceneStack;

public:
	SceneStackManager();
	~SceneStackManager();

	void PushScene(BaseScene* scene);
	void PopScene();
	void RunCurrentScene();
	void UpdateSceneStack(SceneUpdateResult result);
	void CloseGame();
	bool IsEmpty();
};

