#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <string>
#include "Component.h"
#include "CTransform.h"

class CSprite :public Component
{
public:
	LPDIRECT3DTEXTURE9 texture;
	int height;
	int width;
	int rows;
	int cols;
	int maxFrame;
	int rowToDraw;

public:
	CSprite();
	CSprite(int height, int width);
	CSprite(int height, int width, int rows, int cols, int maxFrame, int rowToDraw);

	bool InitializeSprite(IDirect3DDevice9* d3dDevice, std::string fileName);
	bool InitializeSpriteTransparent(IDirect3DDevice9* d3dDevice, std::string, int r, int g, int b);

	void ReleaseSprite();
	//Formula to calculate rectangle
	RECT CalcRect(const int frameCount);
	//Formula to calculate rectangle with position
	RECT CalcRectPosition(const D3DXVECTOR2& position);
	//Simple formula to get the height of sprite out of the spritesheet
	int SpriteHeight();
	//Simple formula to get the width of sprite out of the spritesheet
	int SpriteWidth();
	//Formula to get the center point of sprite
	D3DXVECTOR2 SpriteCenter();
	//FOrmula to get the center point of sprite with position
	D3DXVECTOR2 SpriteCenterPosition(const D3DXVECTOR2& position);

	//Set transformation matrix without actually drawing
	void SetMatrixTransformation(LPD3DXSPRITE spriteBrush, const CTransform& transform);
	//Simply draw sprite based on previous transformation matrix (If was set before drawing)
	void DrawSprite(const int frameCount, LPD3DXSPRITE spriteBrush, const D3DXVECTOR2& position, const int& r, const int& g, const int& b);
	//Draw while setting transformation matrix
	void DrawSpriteWithMatrix(const int frameCount, LPD3DXSPRITE spriteBrush, const CTransform& transform, const int& r, const int& g, const int& b);

	void Update() override;
};

