#include "CPieceUnit.h"

Colors CPieceUnit::GetColor()
{
	return m_color;
}

int CPieceUnit::MovePieceX(int movement)
{
	return m_xIndex += movement;
}

int CPieceUnit::MovePieceY()
{
	return ++m_yIndex;
}

int CPieceUnit::GetXIndex()
{
	return m_xIndex;
}

int CPieceUnit::GetYIndex()
{
	return m_yIndex;
}

void CPieceUnit::SetIndex(int newXIndex, int newYIndex)
{
	m_xIndex = newXIndex;
	m_yIndex = newYIndex;
}
