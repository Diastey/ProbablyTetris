#include "SceneStackManager.h"

SceneStackManager::SceneStackManager()
{
}

SceneStackManager::~SceneStackManager()
{
	CloseGame();
}

void SceneStackManager::PushScene(BaseScene* scene)
{
	scene->Initialize();
	sceneStack.push(scene);
}

void SceneStackManager::PopScene()
{
	sceneStack.top()->Release();
	sceneStack.pop();
}

void SceneStackManager::RunCurrentScene()
{
	UpdateSceneStack(sceneStack.top()->Run());
}

void SceneStackManager::UpdateSceneStack(SceneUpdateResult result)
{
	switch (result.command)
	{
	case None:
		break;
	case Push:
		PushScene(result.nextScene);
		break;
	case Pop:
		PopScene();
		break;
	case Quit:
		CloseGame();
		break;
	}
}

void SceneStackManager::CloseGame()
{
	if (!sceneStack.empty())
	{
		sceneStack.top()->Release();
		sceneStack.pop();
		CloseGame();
	}
}
bool SceneStackManager::IsEmpty()
{
	return sceneStack.empty();
}