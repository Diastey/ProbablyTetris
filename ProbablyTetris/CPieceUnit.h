#pragma once
#include "Component.h"
#include "ColorsUtil.h"

class CPieceUnit :public Component
{
	int m_xIndex;
	int m_yIndex;
	Colors m_color;

public:
	CPieceUnit()
		:m_xIndex(0), m_yIndex(0), m_color(PieceColors::White)
	{
	}
	CPieceUnit(int xPosition, int yPosition, Colors color)
		:m_xIndex(xPosition), m_yIndex(yPosition), m_color(color)
	{
	}

	Colors GetColor();
	int MovePieceX(int movement);
	int MovePieceY();
	int GetXIndex();
	int GetYIndex();
	void SetIndex(int newXPosition, int newYPosition);
};