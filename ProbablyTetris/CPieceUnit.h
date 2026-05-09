#pragma once
#include "Component.h"
#include "Vec2Struct.h"

class CPieceUnit :public Component
{
	int m_xIndex;
	int m_yIndex;
	Vec2f m_localPivot;

public:
	CPieceUnit()
		:m_xIndex(0), m_yIndex(0), m_localPivot({ 0,0 })
	{
	}
	CPieceUnit(int xPosition, int yPosition)
		:m_xIndex(xPosition), m_yIndex(yPosition), m_localPivot({ 0,0 })
	{
	}
	CPieceUnit(int xPosition, int yPosition, Vec2f localPivot)
		:m_xIndex(xPosition), m_yIndex(yPosition), m_localPivot(localPivot)
	{
	}

	int MovePieceX(int movement);
	int MovePieceY();
	int GetLocalXIndex();
	int GetLocalYIndex();
	int GetXIndex(int pivotX);
	int GetYIndex(int pivotY);
	const Vec2f& GetLocalPivot();
	void SetLocalIndex(int newXPosition, int newYPosition);
};