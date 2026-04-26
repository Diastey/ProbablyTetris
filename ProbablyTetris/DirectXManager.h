#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class DirectXManager
{
protected:
	IDirect3D9* direct3D9;
	IDirect3DDevice9* d3dDevice;
	D3DPRESENT_PARAMETERS d3dPP;
	LPD3DXSPRITE spriteBrush;

public:
	DirectXManager();
	~DirectXManager();

	bool CreateDirectX(HWND hWnd, int backBufferWidth, int backBufferHeight);
	void BeginRender();
	void EndRender();
	void ReleaseRender();
	LPD3DXSPRITE GetSpriteBrush();
	IDirect3DDevice9* GetD3dDevice();
	D3DPRESENT_PARAMETERS GetD3dPP();
};

