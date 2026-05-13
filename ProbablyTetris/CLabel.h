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

	float defaultOffset = 1.1;
	//Pass in value
	int m_width;
	int m_height;
	int m_weight;
	int m_wordLength;
	float m_offset;
	bool m_italic;
	Colors m_colors;
	std::string m_fontFamily;
	std::string m_text;

public:
	CLabel()
		:m_width(0), m_height(0), m_weight(0), m_italic(false), m_fontFamily(""), m_text(""), m_wordLength(0), m_colors(OtherColors::Default), m_offset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(""), m_wordLength(0), m_colors(OtherColors::Default), m_offset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, int wordLength)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_wordLength(wordLength), m_colors(OtherColors::Default), m_offset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, int wordLength, Colors color)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_wordLength(wordLength), m_colors(color), m_offset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, int wordLength, Colors color, float offset)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_wordLength(wordLength), m_colors(color), m_offset(offset)
	{
	}

	bool InitializeLabel(IDirect3DDevice9* d3dDevice);
	void ReleaseLabel();
	D3DXVECTOR2 LabelCenter(int wordLength);
	float GetFontWidth();
	void DrawLabel(LPD3DXSPRITE spriteBrush, D3DXVECTOR2 panelPosition, CTransform transform);
	void DrawLabelAtPosition(LPD3DXSPRITE spriteBrush, LPCSTR drawText, int textWordLength, Colors color, CTransform transform);
};

