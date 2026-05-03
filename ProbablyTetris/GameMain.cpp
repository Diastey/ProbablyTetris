#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <string>

#include "GameWindowManager.h"
#include "DirectXManager.h"
#include "InputManager.h"
#include "SceneStackManager.h"

#include "MainScene.h"

#include <iostream>

// HEAP
GameWindowManager* GameWindowManager::instance = nullptr;
DirectXManager* DirectXManager::instance = nullptr;
InputManager* InputManager::instance = nullptr;
SceneStackManager* SceneStackManager::instance = nullptr;

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWindowManager::GetInstance()->InitializeWindow(hInstance, 1024, 800, "ProbablyTetris");

	if (!DirectXManager::GetInstance()->CreateDirectX(GameWindowManager::GetInstance()->GetHWND(), GameWindowManager::GetInstance()->GetWindowWidth(), GameWindowManager::GetInstance()->GetWindowHeight()))
	{
		std::cout << "DirectX create failed" << std::endl;
		return 0;
	}

	if (!InputManager::GetInstance()->CreateInputDevice(GameWindowManager::GetInstance()->GetHWND(), GameWindowManager::GetInstance()->GetWindowWidth(), GameWindowManager::GetInstance()->GetWindowHeight()))
	{
		std::cout << "Input device create failed" << std::endl;
		return 0;
	}

	MainScene* mainScene = new MainScene(60);
	SceneStackManager::GetInstance()->PushScene(mainScene);

	while (GameWindowManager::GetInstance()->IsRunning())
	{
		if (!SceneStackManager::GetInstance()->IsEmpty())
		{
			SceneStackManager::GetInstance()->RunCurrentScene();
		}

		if (InputManager::GetInstance()->IsKeyPressed(DIK_ESCAPE))
		{
			std::cout << "QUIT" << std::endl;
			PostQuitMessage(0);
		}
	}

	InputManager::GetInstance()->ReleaseInputDevice();
	DirectXManager::GetInstance()->ReleaseRender();

	GameWindowManager::GetInstance()->Cleanup();

	return 0;
}