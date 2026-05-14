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

	float defaultOffset = 1.35;
	//Pass in value
	int m_width;
	int m_height;
	int m_weight;
	float m_baseOffset;
	float m_leftOffset = 0;
	float m_rightOffset = 0;
	bool m_italic;
	std::string* m_referenceText = nullptr;
	Colors m_colors;
	std::string m_fontFamily;
	std::string m_text;

public:
	CLabel()
		:m_width(0), m_height(0), m_weight(0), m_italic(false), m_fontFamily(""), m_text(""), m_colors(OtherColors::Default), m_baseOffset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(""), m_colors(OtherColors::Default), m_baseOffset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_colors(OtherColors::Default), m_baseOffset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, float offset)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_colors(OtherColors::Default), m_baseOffset(offset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, Colors color)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_colors(color), m_baseOffset(defaultOffset)
	{
	}
	CLabel(int width, int height, int weight, bool italic, std::string fontFamily, std::string text, Colors color, float offset)
		:m_width(width), m_height(height), m_weight(weight), m_italic(italic), m_fontFamily(fontFamily), m_text(text), m_colors(color), m_baseOffset(offset)
	{
	}

	void SetReference(std::string* stringToObserve);
	void SetOffset(int leftOffset, int rightOffset);
	bool InitializeLabel(IDirect3DDevice9* d3dDevice);
	void SetText(const std::string& newText);
	void ReleaseLabel();
	D3DXVECTOR2 LabelCenter(int wordLength);
	float GetTextWidth();
	void DrawLabel(LPD3DXSPRITE spriteBrush, D3DXVECTOR2 panelPosition, CTransform transform);
};

