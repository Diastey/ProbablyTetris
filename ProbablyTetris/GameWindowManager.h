#pragma once
#include <Windows.h>
#include <string>

class GameWindowManager
{
protected:
	HINSTANCE hInstance;
	HWND g_hWnd;
	WNDCLASS wndClass;
	MSG msg;
	LPCSTR windowTitle;
	LPCSTR windowClassName;
	int windowWidth;
	int windowHeight;

public:
	GameWindowManager(HINSTANCE hInstance, int width, int height, std::string title, std::string className);
	~GameWindowManager();

	void InitializeWindow();
	LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool IsRunning();
	HWND GetHWND();
	int GetWindowWidth();
	int GetWindowHeight();
	void Cleanup();
};