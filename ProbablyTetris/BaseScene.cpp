#include "BaseScene.h"

SceneUpdateResult BaseScene::Run()
{
	m_result.command = None;
	Input();

	Update(m_frameTimer->FramesToUpdate());

	DirectXManager::GetInstance()->BeginRender();
	Render();
	DirectXManager::GetInstance()->EndRender();

	AudioUpdate();
	return m_result;
}

void BaseScene::Input()
{
	InputManager::GetInstance()->GetInput();
}

void BaseScene::AudioUpdate()
{

}

//void BaseScene::UpdateCursorPosition(int cursorObjectIndex)
//{
//
//}

void BaseScene::ReleaseScene()
{
	delete m_frameTimer;

	Release();
}