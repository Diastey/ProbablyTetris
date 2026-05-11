#include "DirectXManager.h"

DirectXManager::~DirectXManager()
{
	ReleaseRender();
}

bool DirectXManager::CreateDirectX(HWND hWnd, int backBufferWidth, int backBufferHeight)
{
	HRESULT hr = NULL;
	m_direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&m_d3dPP, sizeof(m_d3dPP));

	m_d3dPP.Windowed = true;
	m_d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dPP.BackBufferCount = 1;
	m_d3dPP.BackBufferWidth = backBufferWidth;
	m_d3dPP.BackBufferHeight = backBufferHeight;
	m_d3dPP.hDeviceWindow = hWnd;

	hr = m_direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dPP, &m_d3dDevice);
	if (FAILED(hr))
	{
		return false;
	}
	hr = D3DXCreateSprite(m_d3dDevice, &m_spriteBrush);
	if (FALSE(hr))
	{
		return false;
	}

	return true;
}

void DirectXManager::BeginRender()
{
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_d3dDevice->BeginScene();
	m_spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
}

void DirectXManager::EndRender()
{
	m_spriteBrush->End();
	m_d3dDevice->EndScene();

	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectXManager::ReleaseRender()
{
	m_spriteBrush->Release();
	m_spriteBrush = NULL;

	m_d3dDevice->Release();
	m_d3dDevice = NULL;

	m_direct3D9->Release();
	m_direct3D9 = NULL;
}

LPD3DXSPRITE DirectXManager::GetSpriteBrush()
{
	return m_spriteBrush;
}

IDirect3DDevice9* DirectXManager::GetD3dDevice()
{
	return m_d3dDevice;
}

D3DPRESENT_PARAMETERS DirectXManager::GetD3dPP()
{
	return m_d3dPP;
}
