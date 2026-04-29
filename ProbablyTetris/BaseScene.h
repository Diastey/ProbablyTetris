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
	SceneCommand command;
	BaseScene* nextScene = nullptr;
};

class BaseScene
{
	int m_fps;
	HINSTANCE m_hInstance;
	GameWindowManager* m_window;
	DirectXManager* m_directX;
	InputManager* m_input;

	SceneUpdateResult result;
	std::vector<GameObject> m_gameObjects;
	FrameTimer* m_frameTimer;
	int m_frames = 1;

public:
	BaseScene(int fps, HINSTANCE hInstance, GameWindowManager* window, DirectXManager* directX, InputManager* input);
	virtual ~BaseScene() = default;

	SceneUpdateResult Run();
	void Input();
	void AudioUpdate();
	void UpdateCursorPosition(int cursorObjectIndex);

	virtual void Release() = 0;
	virtual bool Initialize() = 0;
	virtual void Update(int frames) = 0;
	virtual void Render() = 0;
};