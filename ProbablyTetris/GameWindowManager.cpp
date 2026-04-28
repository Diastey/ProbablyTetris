#pragma once
#include "GameWindowManager.h"

namespace GameWindowPTR
{
	GameWindowManager* globalPtr;
}

LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GameWindowPTR::globalPtr->WindowProcedure(hWnd, message, wParam, lParam);
}

GameWindowManager::GameWindowManager(HINSTANCE hInstance, int width, int height, std::string title)
	:hInstance(hInstance)
	, windowWidth(width)
	, windowHeight(height)
	, windowTitle(title)
{
}

GameWindowManager::~GameWindowManager()
{
	Cleanup();
}

void GameWindowManager::InitializeWindow()
{
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = MainWindowProcedure;
	wndClass.lpszClassName = "CPPPROJECT";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, windowTitle.c_str(), WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

	ShowWindow(g_hWnd, 1);
	ShowCursor(true);
	ZeroMemory(&msg, sizeof(msg));
}

LRESULT GameWindowManager::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool GameWindowManager::IsRunning()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return true;
}

HWND GameWindowManager::GetHWND()
{
	return g_hWnd;
}

int GameWindowManager::GetWindowWidth()
{
	return windowWidth;
}

int GameWindowManager::GetWindowHeight()
{
	return windowHeight;
}

void GameWindowManager::Cleanup()
{
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}
