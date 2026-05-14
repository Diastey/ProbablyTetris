#include "BaseScene.h"

SceneUpdateResult BaseScene::Run()
{
	m_result.command = None;
	Input();

	Update(m_frameTimer->FramesToUpdate());

	if (m_result.command == None)
	{
		DirectXManager::GetInstance()->BeginRender();
		Render();
		DirectXManager::GetInstance()->EndRender();
		AudioUpdate();
	}
	return m_result;
}

void BaseScene::Input()
{
	InputManager::GetInstance()->GetInput();
}

void BaseScene::AudioUpdate()
{
	AudioManager::GetInstance()->UpdateSounds();
}

void BaseScene::ReleaseScene()
{
	delete m_frameTimer;
	m_screenPanel.ReleasePanel();

	Release();
}