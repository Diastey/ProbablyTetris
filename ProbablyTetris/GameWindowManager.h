#pragma once
#include <Windows.h>
#include <string>

class GameWindowManager
{
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	WNDCLASS m_wndClass;
	MSG m_msg;
	const std::string m_windowTitle;
	int m_windowWidth;
	int m_windowHeight;

public:
	GameWindowManager(HINSTANCE hInstance, int width, int height, std::string title);
	~GameWindowManager();

	void InitializeWindow();
	LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool IsRunning();
	HWND GetHWND();
	int GetWindowWidth();
	int GetWindowHeight();
	void Cleanup();
};