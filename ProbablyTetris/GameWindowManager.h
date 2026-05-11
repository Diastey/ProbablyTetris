#pragma once
#include <Windows.h>
#include <string>

class GameWindowManager
{
	static GameWindowManager* instance;

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	WNDCLASS m_wndClass;
	MSG m_msg;
	std::string m_windowTitle;
	int m_windowWidth;
	int m_windowHeight;

public:
	GameWindowManager() = default;
	~GameWindowManager();
	static GameWindowManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameWindowManager();
		}
		return instance;
	}

	void InitializeWindow(HINSTANCE hInstance, int width, int height, std::string title);
	LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool IsRunning();
	HINSTANCE GetHInstance();
	HWND GetHWND();
	int GetWindowWidth();
	int GetWindowHeight();
	void Cleanup();
	static void DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
};