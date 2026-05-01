#include "CSprite.h"

CSprite::CSprite()
{
	texture = NULL;
	height = 0;
	width = 0;
	rows = 0;
	cols = 0;
	maxFrame = 0;
	rowToDraw = 0;
}

CSprite::CSprite(int height, int width)
	:height(height), width(width), rows(1), cols(1), maxFrame(1), rowToDraw(0)
{
	texture = NULL;
}

CSprite::CSprite(int height, int width, int rows, int cols, int maxFrame, int rowToDraw)
	:height(height), width(width), rows(rows), cols(cols), maxFrame(maxFrame), rowToDraw(rowToDraw)
{
	texture = NULL;
}

//Initialize the sprite by create texture based on texture file name
bool CSprite::InitializeSprite(IDirect3DDevice9* d3dDevice, std::string fileName)
{
	HRESULT hr = NULL;

	hr = D3DXCreateTextureFromFile(d3dDevice, fileName.c_str(), &texture);
	if (FALSE(hr)) {
		return false;
	}
	return true;
}

//Initialize the sprite by create texture that is transparent in specific color based on texture file name
bool CSprite::InitializeSpriteTransparent(IDirect3DDevice9* d3dDevice, std::string fileName, int r, int g, int b)
{
	HRESULT hr = NULL;

	hr = D3DXCreateTextureFromFileEx(d3dDevice, fileName.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(r, g, b), NULL, NULL, &texture);
	if (FALSE(hr)) {
		return false;
	}
	return true;
}

//Release the texture object
void CSprite::ReleaseSprite()
{
	texture->Release();
	texture = NULL;
}

//Formula to calculate rectangle
RECT CSprite::CalcRect(const int frameCount)
{
	RECT rect;

	//Calculate the rectangle of the sprite based on different frame count changed in each frame
	rect.top = (rowToDraw * SpriteHeight()) + (((frameCount % maxFrame) % rows) * SpriteHeight());
	rect.bottom = rect.top + SpriteHeight();
	rect.left = (SpriteWidth() * (frameCount % cols));
	rect.right = rect.left + SpriteWidth();

	return rect;
}

//Formula to calculate rectangle with position
RECT CSprite::CalcRectPosition(const D3DXVECTOR2& position)
{
	RECT rect;

	// Calculate the rectangle of the sprite based on the position of the sprite 
	rect.top = position.y;
	rect.bottom = rect.top + SpriteHeight();
	rect.left = position.x;
	rect.right = rect.left + SpriteWidth();

	return rect;
}

//Simple formula to get the height of sprite out of the spritesheet
int CSprite::SpriteHeight()
{
	return  height / rows;
}

//Simple formula to get the width of sprite out of the spritesheet
int CSprite::SpriteWidth()
{
	return width / cols;
}

//Formula to get the center point of sprite
D3DXVECTOR2 CSprite::SpriteCenter()
{
	return D3DXVECTOR2(SpriteWidth() / 2, SpriteHeight() / 2);
}

//Formula to get the center point of sprite with position
D3DXVECTOR2 CSprite::SpriteCenterPosition(const D3DXVECTOR2& position)
{
	return D3DXVECTOR2(position.x + SpriteCenter().x, position.y + SpriteCenter().y);
}

//Set transformation matrix without actually drawing
void CSprite::SetMatrixTransformation(LPD3DXSPRITE spriteBrush, const CTransform& transform)
{
	D3DXMATRIX matrix;
	D3DXVECTOR2 spriteCenter = SpriteCenter();
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &transform.scaling, &spriteCenter, transform.rotation, &transform.position);
	spriteBrush->SetTransform(&matrix);
}

//Simply draw sprite based on previous transformation matrix (If was set before drawing)
void CSprite::DrawSprite(const int frameCount, LPD3DXSPRITE spriteBrush, const D3DXVECTOR2& position, const int& r, const int& g, const int& b)
{
	RECT rect = CalcRect(frameCount);
	D3DXVECTOR3 position3D(position.x, position.y, 0);
	spriteBrush->Draw(texture, &rect, NULL, &position3D, D3DCOLOR_XRGB(r, g, b));
}

//Draw while setting transformation matrix
void CSprite::DrawSpriteWithMatrix(const int frameCount, LPD3DXSPRITE spriteBrush, const CTransform& transform, const int& r, const int& g, const int& b)
{
	D3DXMATRIX matrix;
	RECT rect = CalcRect(frameCount);
	D3DXVECTOR2 spriteCenter = SpriteCenter();
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &transform.scaling, &spriteCenter, transform.rotation, &transform.position);
	spriteBrush->SetTransform(&matrix);
	spriteBrush->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(r, g, b));
}

void CSprite::Update()
{
}
