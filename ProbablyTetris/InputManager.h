#pragma once
#include <dinput.h>

class InputManager
{
	static InputManager* instance;

	LPDIRECTINPUT8 m_dInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_dInputKeyboardDevice = nullptr;
	BYTE m_previousKeyFlags[256];
	BYTE m_currentKeyFlags[256];

public:
	InputManager()
	{
		ZeroMemory(m_previousKeyFlags, 256);
		ZeroMemory(m_currentKeyFlags, 256);
	}
	~InputManager();
	static InputManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new InputManager();
		}
		return instance;
	}

	bool CreateInputDevice(HWND hWnd);
	void GetInput();
	void ReleaseInputDevice();
	bool HasAnyKeyInput();
	bool IsKeyDown(int key);
	bool IsKeyPressed(int key);
	bool IsKeyUp(int key);
	static void DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
};

