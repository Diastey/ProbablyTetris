#pragma once
#include <dinput.h>

class InputManager
{
	static InputManager* instance;

	LPDIRECTINPUT8 m_dInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_dInputKeyboardDevice = nullptr;
	LPDIRECTINPUTDEVICE8 m_dInputMouseDevice = nullptr;
	BYTE m_previousKeyFlags[256];
	BYTE m_currentKeyFlags[256];
	DIMOUSESTATE m_mouseState;
	bool m_mouseDown[2];
	bool m_mouseUp[2];

public:
	LONG currentXpos = 0;
	LONG currentYpos = 0;

public:
	InputManager()
	{
		ZeroMemory(m_previousKeyFlags, 256);
		ZeroMemory(m_currentKeyFlags, 256);
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));

		m_mouseDown[0] = false;
		m_mouseDown[1] = false;
		m_mouseUp[0] = false;
		m_mouseUp[1] = false;
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

	bool CreateInputDevice(HWND hWnd, int backBufferWidth, int backBufferHeight);
	void GetInput();
	void ReleaseInputDevice();
	DIMOUSESTATE GetMouseState();
	bool HasAnyKeyInput();
	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);
	bool IsKeyUp(int key);
	bool IsMouseUp(int key);
	bool IsMouseDown(int key);
	static void DestroyInstance()
	{
		delete instance;
		instance = nullptr;
	}
};

