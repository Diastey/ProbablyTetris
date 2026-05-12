#include "CPieceUnit.h"

int CPieceUnit::MovePieceX(int movement)
{
	return m_xIndex += movement;
}

int CPieceUnit::MovePieceY()
{
	return ++m_yIndex;
}

int CPieceUnit::GetLocalXIndex()
{
	return m_xIndex;
}

int CPieceUnit::GetLocalYIndex()
{
	return m_yIndex;
}

#include <iostream>
int CPieceUnit::GetXIndex(int pivotX)
{
	return m_xIndex + pivotX;
}

int CPieceUnit::GetYIndex(int pivotY)
{
	return m_yIndex + pivotY;
}

const Vec2f& CPieceUnit::GetLocalPivot()
{
	return m_localPivot;
}

void CPieceUnit::SetLocalIndex(int newXIndex, int newYIndex)
{
	m_xIndex = newXIndex;
	m_yIndex = newYIndex;
}

void CPieceUnit::SetLocalPivot(Vec2f newLocalPivot)
{
	m_localPivot = newLocalPivot;
}
