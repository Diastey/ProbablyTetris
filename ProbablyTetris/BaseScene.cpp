#include "BaseScene.h"

BaseScene::BaseScene(int fps)
	:m_frameTimer(new FrameTimer(fps))
{
}

SceneUpdateResult BaseScene::Run()
{
	result.command = None;
	Input();

	Update(m_frameTimer->FramesToUpdate());

	DirectXManager::GetInstance()->BeginRender();
	Render();
	DirectXManager::GetInstance()->EndRender();

	AudioUpdate();
	return result;
}

void BaseScene::Input()
{
	InputManager::GetInstance()->GetInput();
}

void BaseScene::AudioUpdate()
{

}

void BaseScene::UpdateCursorPosition(int cursorObjectIndex)
{

}