#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <string>
#include "Component.h"
#include "CTransform.h"
#include "ColorsUtil.h"

class CSprite :public Component
{
	LPDIRECT3DTEXTURE9 m_texture;
	int m_height;
	int m_width;
	int m_rows;
	int m_cols;
	int m_maxFrame;
	int m_rowToDraw;

public:
	CSprite()
	{
		m_texture = NULL;
		m_height = 0;
		m_width = 0;
		m_rows = 0;
		m_cols = 0;
		m_maxFrame = 0;
		m_rowToDraw = 0;
	}
	CSprite(int height, int width)
		:m_height(height), m_width(width), m_rows(1), m_cols(1), m_maxFrame(1), m_rowToDraw(0)
	{
		m_texture = NULL;
	}
	CSprite(int height, int width, int rows, int cols, int maxFrame, int rowToDraw)
		:m_height(height), m_width(width), m_rows(rows), m_cols(cols), m_maxFrame(maxFrame), m_rowToDraw(rowToDraw)
	{
		m_texture = NULL;
	}

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
	void DrawSprite(LPD3DXSPRITE spriteBrush, const D3DXVECTOR2& position, const int& r, const int& g, const int& b);
	void DrawSprite(LPD3DXSPRITE spriteBrush, const D3DXVECTOR2& position, const Colors& color);
	void DrawSprite(const int frameCount, LPD3DXSPRITE spriteBrush, const D3DXVECTOR2& position, const int& r, const int& g, const int& b);
	//Draw while setting transformation matrix
	void DrawSpriteWithMatrix(const int frameCount, LPD3DXSPRITE spriteBrush, const CTransform& transform, const int& r, const int& g, const int& b);

	void Update() override;

	void Release() override
	{
		ReleaseSprite();
	}
};

