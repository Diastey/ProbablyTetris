#include "BaseScene.h"

BaseScene::BaseScene(int fps, HINSTANCE hInstance, GameWindowManager* window, DirectXManager* directX, InputManager* input)
	:m_fps(fps), m_hInstance(hInstance), m_window(window), m_directX(directX), m_input(input), m_frames(1), m_frameTimer(new FrameTimer())
{
}

SceneUpdateResult BaseScene::Run()
{
	result.command = None;
	Input();
	Update(m_frameTimer->FramesToUpdate());
	Render();
	AudioUpdate();
	return result;
}

void BaseScene::Input()
{
	m_input->GetInput();
}

void BaseScene::AudioUpdate()
{

}

void BaseScene::UpdateCursorPosition(int cursorObjectIndex)
{

}