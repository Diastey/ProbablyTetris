#pragma once
#include <dinput.h>

class InputManager
{
	static InputManager* instance;

	InputManager() = default;
	~InputManager() = default;

	LPDIRECTINPUT8 m_dInput;
	LPDIRECTINPUTDEVICE8 m_dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8 m_dInputMouseDevice;
	BYTE m_previousKeyFlags[256];
	BYTE m_currentKeyFlags[256];
	DIMOUSESTATE m_mouseState;
	bool m_mouseDown[2];
	bool m_mouseUp[2];

public:
	LONG currentXpos;
	LONG currentYpos;

public:
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
	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);
	bool IsKeyUp(int key);
	bool IsMouseUp(int key);
	bool IsMouseDown(int key);
};

