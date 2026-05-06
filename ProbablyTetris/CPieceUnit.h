#pragma once
#include "Component.h"
#include "ColorsUtil.h"
#include "MathUtil.h"

class CPieceUnit :public Component
{
	int m_xIndex;
	int m_yIndex;
	Colors m_color;
	Vec2f m_localPivot;
	bool locked = false;

public:
	CPieceUnit()
		:m_xIndex(0), m_yIndex(0), m_localPivot({ 0,0 }), m_color(PieceColors::White)
	{
	}
	CPieceUnit(int xPosition, int yPosition, Vec2f localPivot, Colors color)
		:m_xIndex(xPosition), m_yIndex(yPosition), m_localPivot(localPivot), m_color(color)
	{
	}

	Colors GetColor();
	int MovePieceX(int movement);
	int MovePieceY();
	int GetLocalXIndex();
	int GetLocalYIndex();
	int GetXIndex(int pivotX);
	int GetYIndex(int pivotY);
	const Vec2f& GetLocalPivot();
	void SetLocalIndex(int newXPosition, int newYPosition);
};