#pragma once
#include <Windows.h>
#include <vector>

#include "GameObject.h"
#include "GameWindowManager.h"
#include "DirectXManager.h"
#include "InputManager.h"
#include "FrameTimer.h"

class BaseScene;

enum SceneCommand
{
	None = 0,
	Push = 1,
	Pop = 2,
	Quit = 3
};

struct SceneUpdateResult
{
	SceneCommand command = None;
	BaseScene* nextScene = nullptr;
};

class BaseScene
{
protected:
	SceneUpdateResult m_result;
	std::vector<GameObject> m_gameObjects;
	FrameTimer* m_frameTimer;
	int m_currentFrame = 1;

public:
	BaseScene(int fps)
		:m_frameTimer(new FrameTimer(fps))
	{
	}
	virtual ~BaseScene() = default;

	SceneUpdateResult Run();
	void Input();
	void AudioUpdate();
	void UpdateCursorPosition(int cursorObjectIndex);
	void ReleaseScene();

	virtual bool Initialize() = 0;
	virtual void Update(int frames) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};