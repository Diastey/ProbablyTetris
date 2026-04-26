#include "DirectXManager.h"

DirectXManager::DirectXManager()
{
}

DirectXManager::~DirectXManager()
{
}

bool DirectXManager::CreateDirectX(HWND hWnd, int backBufferWidth, int backBufferHeight)
{
	HRESULT hr = NULL;
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&d3dPP, sizeof(d3dPP));

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = backBufferWidth;
	d3dPP.BackBufferHeight = backBufferHeight;
	d3dPP.hDeviceWindow = hWnd;

	hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	if (FAILED(hr)) 
	{
		return false;
	}
	hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
	if (FALSE(hr)) 
	{
		return false;
	}

	return true;
}

void DirectXManager::BeginRender()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();
	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
}

void DirectXManager::EndRender()
{
	spriteBrush->End();
	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectXManager::ReleaseRender()
{
	spriteBrush->Release();
	spriteBrush = NULL;

	d3dDevice->Release();
	d3dDevice = NULL;

	direct3D9->Release();
	direct3D9 = NULL;
}

LPD3DXSPRITE DirectXManager::GetSpriteBrush()
{
	return spriteBrush;
}

IDirect3DDevice9* DirectXManager::GetD3dDevice()
{
	return d3dDevice;
}

D3DPRESENT_PARAMETERS DirectXManager::GetD3dPP()
{
	return d3dPP;
}
