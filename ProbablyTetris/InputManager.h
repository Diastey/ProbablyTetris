#pragma once
#include <dinput.h>

class InputManager
{
protected:
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
	LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	BYTE diKeys[256];
	DIMOUSESTATE mouseState;
	bool mouseDown[2];
	bool mouseUp[2];

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

