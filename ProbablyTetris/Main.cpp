#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include <string>

#include "GameWindowManager.h"
#include "DirectXManager.h"
#include "InputManager.h"

#include <iostream>

// HEAP
GameWindowManager* windowManager;
DirectXManager* directXManager;
InputManager* inputManager;

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	windowManager = new GameWindowManager(hInstance, 1024, 640, "ProbablyTetris", "PBYTS");
	windowManager->InitializeWindow();

	directXManager = new DirectXManager();
	if (!directXManager->CreateDirectX(windowManager->GetHWND(), windowManager->GetWindowWidth(), windowManager->GetWindowHeight()))
	{
		return 0;
	}

	if (!inputManager->CreateInputDevice(windowManager->GetHWND(), windowManager->GetWindowWidth(), windowManager->GetWindowHeight()))
	{
		return 0;
	}

	while (windowManager->IsRunning())
	{
		//std::cout << "Running" << std::endl;
	}

	inputManager->ReleaseInputDevice();
	directXManager->ReleaseRender();

	windowManager->Cleanup();

	return 0;
}