#pragma once
#include <dinput.h>

class InputManager
{
	LPDIRECTINPUT8 m_dInput;
	LPDIRECTINPUTDEVICE8 m_dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8 m_dInputMouseDevice;
	BYTE m_diKeys[256];
	DIMOUSESTATE m_mouseState;
	bool m_mouseDown[2];
	bool m_mouseUp[2];

public:
	LONG currentXpos;
	LONG currentYpos;

public:
	InputManager();
	~InputManager();

	bool CreateInputDevice(HWND hWnd, int backBufferWidth, int backBufferHeight);
	void GetInput();
	void ReleaseInputDevice();
	DIMOUSESTATE GetMouseState();
	bool IsKeyPressed(int key);
	bool IsMouseUp(int key);
	bool IsMouseDown(int key);
};

