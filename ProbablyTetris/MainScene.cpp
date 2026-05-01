#include "MainScene.h"

#include <iostream>

MainScene::MainScene(int fps)
	:BaseScene(fps)
{
}

bool MainScene::Initialize()
{
	CSprite testSprite = CSprite(64, 64);
	if (!testSprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Block.png"))
	{
		return false;
	}

	GameObject testGO = GameObject();
	testGO.Add<CSprite>(testSprite);
	m_gameObjects.push_back(testGO);

	return true;
}

void MainScene::Update(int frames)
{
	if (InputManager::GetInstance()->IsMouseDown(0))
	{
		std::cout << m_gameObjects.size() << std::endl;
	}
}

void MainScene::Render()
{
	for (GameObject& obj : m_gameObjects)
	{
		obj.Get<CSprite>().DrawSprite(m_currentFrame, DirectXManager::GetInstance()->GetSpriteBrush(), D3DXVECTOR2(0, 0), 255, 0, 0);
	}
}

void MainScene::Release()
{
}