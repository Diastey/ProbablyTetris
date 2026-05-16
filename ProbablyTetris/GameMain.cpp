#pragma once
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "fmod_vc.lib")

#include "GameWindowManager.h"
#include "DirectXManager.h"
#include "InputManager.h"
#include "SceneStackManager.h"
#include "AudioManager.h"

#include "MainScene.h"

#include <iostream>

// HEAP
GameWindowManager* GameWindowManager::instance = nullptr;
DirectXManager* DirectXManager::instance = nullptr;
InputManager* InputManager::instance = nullptr;
SceneStackManager* SceneStackManager::instance = nullptr;
AudioManager* AudioManager::instance = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
//int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWindowManager::GetInstance()->InitializeWindow(hInstance, 1024, 800, "ProbablyTetris");

	if (!DirectXManager::GetInstance()->CreateDirectX(GameWindowManager::GetInstance()->GetHWND(), GameWindowManager::GetInstance()->GetWindowWidth(), GameWindowManager::GetInstance()->GetWindowHeight()))
	{
		std::cout << "DirectX create failed" << std::endl;
		return 0;
	}

	if (!InputManager::GetInstance()->CreateInputDevice(GameWindowManager::GetInstance()->GetHWND()))
	{
		std::cout << "Input device create failed" << std::endl;
		return 0;
	}

	AudioManager::GetInstance()->InitializeAudio();

	MainScene* mainScene = new MainScene(30);
	SceneStackManager::GetInstance()->PushScene(mainScene);

	while (GameWindowManager::GetInstance()->IsRunning())
	{
		if (!SceneStackManager::GetInstance()->IsEmpty())
		{
			SceneStackManager::GetInstance()->RunCurrentScene();
		}
	}

	//InputManager::GetInstance()->ReleaseInputDevice();
	//DirectXManager::GetInstance()->ReleaseRender();

	//GameWindowManager::GetInstance()->Cleanup();

	SceneStackManager::DestroyInstance();
	InputManager::DestroyInstance();
	DirectXManager::DestroyInstance();
	GameWindowManager::DestroyInstance();
	AudioManager::DestroyInstance();

	return 0;
}