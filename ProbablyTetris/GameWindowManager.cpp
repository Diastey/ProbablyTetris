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
	:m_hInstance(hInstance)
	, m_windowWidth(width)
	, m_windowHeight(height)
	, m_windowTitle(title)
{
}

GameWindowManager::~GameWindowManager()
{
	Cleanup();
}

void GameWindowManager::InitializeWindow()
{
	ZeroMemory(&m_wndClass, sizeof(m_wndClass));
	m_wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wndClass.hInstance = m_hInstance;
	m_wndClass.lpfnWndProc = MainWindowProcedure;
	m_wndClass.lpszClassName = "CPPPROJECT";
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&m_wndClass);
	m_hWnd = CreateWindowEx(0, m_wndClass.lpszClassName, m_windowTitle.c_str(), WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN) / 2 - m_windowWidth / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - m_windowHeight / 2, m_windowWidth, m_windowHeight, NULL, NULL, m_hInstance, NULL);

	ShowWindow(m_hWnd, 1);
	ShowCursor(true);
	ZeroMemory(&m_msg, sizeof(m_msg));
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
	if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		if (m_msg.message == WM_QUIT)
		{
			return false;
		}
		else
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	}
	return true;
}

HWND GameWindowManager::GetHWND()
{
	return m_hWnd;
}

int GameWindowManager::GetWindowWidth()
{
	return m_windowWidth;
}

int GameWindowManager::GetWindowHeight()
{
	return m_windowHeight;
}

void GameWindowManager::Cleanup()
{
	UnregisterClass(m_wndClass.lpszClassName, GetModuleHandle(NULL));
}
