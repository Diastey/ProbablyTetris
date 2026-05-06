#include "InputManager.h"

bool InputManager::CreateInputDevice(HWND hWnd, int backBufferWidth, int backBufferHeight)
{
	HRESULT hr = NULL;
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&m_dInput, NULL);
	if (FALSE(hr))
	{
		return false;
	}

	hr = m_dInput->CreateDevice(GUID_SysKeyboard, &m_dInputKeyboardDevice, NULL);
	if (FALSE(hr))
	{
		return false;
	}
	m_dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	m_dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	hr = m_dInput->CreateDevice(GUID_SysMouse, &m_dInputMouseDevice, NULL);
	if (FALSE(hr))
	{
		return false;
	}
	m_dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	m_dInputMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	currentXpos = backBufferWidth / 2;
	currentYpos = backBufferHeight / 2;

	return true;
}

void InputManager::GetInput()
{
	memcpy(m_previousKeyFlags, m_currentKeyFlags, 256);

	m_mouseUp[0] = false;
	m_mouseUp[1] = false;
	m_dInputKeyboardDevice->Acquire();
	m_dInputMouseDevice->Acquire();
	m_dInputKeyboardDevice->GetDeviceState(256, m_currentKeyFlags);
	m_dInputMouseDevice->GetDeviceState(sizeof(m_mouseState), &m_mouseState);

	if (IsMouseDown(0))
	{
		m_mouseDown[0] = true;
	}
	else if (m_mouseDown[0])
	{
		m_mouseUp[0] = true;
		m_mouseDown[0] = false;
	}

	if (IsMouseDown(1))
	{
		m_mouseDown[1] = true;
	}
	else if (m_mouseDown[1])
	{
		m_mouseUp[1] = true;
		m_mouseDown[1] = false;
	}

	currentXpos += m_mouseState.lX;
	currentYpos += m_mouseState.lY;
}

bool InputManager::IsKeyPressed(int key)
{
	return (m_currentKeyFlags[key] & 0x80);
}

bool InputManager::IsKeyDown(int key)
{
	return (m_currentKeyFlags[key] & 0x80) && !(m_previousKeyFlags[key] & 0x80);
}

bool InputManager::IsKeyUp(int key)
{

	return !(m_currentKeyFlags[key] & 0x80) && (m_previousKeyFlags[key] & 0x80);
}

bool InputManager::IsMouseUp(int key)
{
	return m_mouseUp[key];
}

bool InputManager::IsMouseDown(int key)
{
	return (GetMouseState().rgbButtons[0] & 0x80);
}

void InputManager::ReleaseInputDevice()
{
	m_dInputMouseDevice->Unacquire();
	m_dInputMouseDevice->Release();
	m_dInputMouseDevice = NULL;

	m_dInputKeyboardDevice->Unacquire();
	m_dInputKeyboardDevice->Release();
	m_dInputKeyboardDevice = NULL;

	m_dInput->Release();
	m_dInput = NULL;
}

DIMOUSESTATE InputManager::GetMouseState()
{
	return m_mouseState;
}
