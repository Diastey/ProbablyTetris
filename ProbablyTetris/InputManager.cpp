#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::CreateInputDevice(HWND hWnd, int backBufferWidth, int backBufferHeight)
{
	HRESULT hr = NULL;
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	if (FALSE(hr)) 
	{
		return false;
	}

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FALSE(hr)) 
	{
		return false;
	}
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FALSE(hr))
	{
		return false;
	}
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);

	currentXpos = backBufferWidth / 2;
	currentYpos = backBufferHeight / 2;

	return true;
}

void InputManager::GetInput()
{
	mouseUp[0] = false;
	mouseUp[1] = false;
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	if (IsMouseDown(0))
	{
		mouseDown[0] = true;
	}
	else if (mouseDown[0])
	{
		mouseUp[0] = true;
		mouseDown[0] = false;
	}

	if (IsMouseDown(1))
	{
		mouseDown[1] = true;
	}
	else if (mouseDown[1])
	{
		mouseUp[1] = true;
		mouseDown[1] = false;
	}

	currentXpos += mouseState.lX;
	currentYpos += mouseState.lY;
}

bool InputManager::IsKeyPressed(int key)
{
	if (diKeys[key] & 0x80) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IsMouseUp(int key)
{
	return mouseUp[key];
}

bool InputManager::IsMouseDown(int key)
{
	return (GetMouseState().rgbButtons[0] & 0x80);
}

void InputManager::ReleaseInputDevice()
{
	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInput->Release();
	dInput = NULL;
}

DIMOUSESTATE InputManager::GetMouseState()
{
	return mouseState;
}
