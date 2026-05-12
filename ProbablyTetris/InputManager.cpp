#include "InputManager.h"

InputManager::~InputManager()
{
	ReleaseInputDevice();
}

bool InputManager::CreateInputDevice(HWND hWnd)
{
	HRESULT hr = NULL;
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&m_dInput, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_dInput->CreateDevice(GUID_SysKeyboard, &m_dInputKeyboardDevice, NULL);
	if (FAILED(hr))
	{
		return false;
	}
	m_dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	m_dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	return true;
}

//bool InputManager::CreateInputDevice(HWND hWnd, int backBufferWidth, int backBufferHeight)
//{
//	HRESULT hr = NULL;
//	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&m_dInput, NULL);
//	if (FAILED(hr))
//	{
//		return false;
//	}
//
//	hr = m_dInput->CreateDevice(GUID_SysKeyboard, &m_dInputKeyboardDevice, NULL);
//	if (FAILED(hr))
//	{
//		return false;
//	}
//	m_dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
//	m_dInputKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//
//	hr = m_dInput->CreateDevice(GUID_SysMouse, &m_dInputMouseDevice, NULL);
//	if (FAILED(hr))
//	{
//		return false;
//	}
//	m_dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
//	m_dInputMouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//	currentXpos = backBufferWidth / 2;
//	currentYpos = backBufferHeight / 2;
//
//	return true;
//}

void InputManager::GetInput()
{
	memcpy(m_previousKeyFlags, m_currentKeyFlags, 256);
	m_dInputKeyboardDevice->Acquire();
	m_dInputKeyboardDevice->GetDeviceState(256, m_currentKeyFlags);
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

void InputManager::ReleaseInputDevice()
{
	m_dInputKeyboardDevice->Unacquire();
	m_dInputKeyboardDevice->Release();
	m_dInputKeyboardDevice = NULL;

	m_dInput->Release();
	m_dInput = NULL;
}

bool InputManager::HasAnyKeyInput()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_currentKeyFlags[i] & 0x80)
			return true;
	}

	return false;
}
