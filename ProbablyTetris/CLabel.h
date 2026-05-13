#pragma once
#include "Component.h"
#include "DirectXManager.h"
#include "ColorsDef.h"
#include "CTransform.h"

#include <string>
#include <d3d9types.h>

class CLabel :public Component
{
	LPD3DXFONT m_label = NULL;

	//Pass in value
	int m_width;
	int m_height;
	int m_weight;
	int m_wordLength;
	bool m_italic;
	Colors m_colors;
	LPCTSTR m_fontFamily;
	LPCTSTR m_text;
public:
	CLabel()
		:m_width(0), m_height(0), m_weight(0), m_italic(false), m_fontFamily(""), m_text(""), m_wordLength(0), m_colors({ 255,255,255 })
	{

	}
	CLabel(int width, int height, int weight, bool italic, LPCTSTR fontFamily)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(""), m_wordLength(0), m_colors({ 255,255,255 })
	{

	}
	CLabel(int width, int height, int weight, bool italic, LPCTSTR fontFamily, LPCSTR text, int wordLength, Colors color)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_wordLength(wordLength), m_colors(color)
	{

	}

	bool InitializeLabel(IDirect3DDevice9* d3dDevice);
	void ReleaseLabel();
	D3DXVECTOR2 LabelCenter(int wordLength);
	void DrawLabel(LPD3DXSPRITE spriteBrush, D3DXVECTOR2 panelPosition, CTransform transform);
	void DrawLabelAtPosition(LPD3DXSPRITE spriteBrush, LPCSTR drawText, int textWordLength, Colors color, CTransform transform);
};

