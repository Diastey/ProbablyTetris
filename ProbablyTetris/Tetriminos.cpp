#include "Tetriminos.h"

#include <iostream>

void Tetriminos::Init(CSprite sprite, Tetrimino tetrimino)
{
	m_pivotPoint = tetrimino.pivotPoint;
	m_matrixSize = tetrimino.pieceMatrixSize;
	m_locked = false;

	for (int i = 0;i < 4;i++)
	{
		GameObject newUnit = GameObject();
		newUnit.Add<CSprite>(sprite);
		CPieceUnit newPiece = CPieceUnit(tetrimino.pieces[i].xIndex, tetrimino.pieces[i].yIndex, tetrimino.color);
		newUnit.Add<CPieceUnit>(newPiece);
		m_units[i] = newUnit;
	}
}

TetrminoUnits& Tetriminos::GetPieces()
{
	return m_units;
}

bool Tetriminos::IsLocked()
{
	return m_locked;
}

bool Tetriminos::RotatePiece(RotateDir rotateDirection)
{
	switch (rotateDirection)
	{
	case CW:
		switch (m_currentDir)
		{
		case TOP:
			m_currentDir = RIGHT;
			break;
		case RIGHT:
			m_currentDir = BOTTOM;
			break;
		case BOTTOM:
			m_currentDir = LEFT;
			break;
		case LEFT:
			m_currentDir = TOP;
			break;
		}
		break;
	case CCW:
		switch (m_currentDir)
		{
		case TOP:
			m_currentDir = LEFT;
			break;
		case LEFT:
			m_currentDir = BOTTOM;
			break;
		case BOTTOM:
			m_currentDir = RIGHT;
			break;
		case RIGHT:
			m_currentDir = TOP;
			break;
		}
		break;
	}

	return true;
}

bool Tetriminos::MovePiece(int moveDirection)
{
	return false;
}

bool Tetriminos::DropPiece(int amount)
{
	return false;
}

void Tetriminos::DrawPiece(int matrixStartX, int matrixStartY, int spriteSize)
{
	for (int i = 0;i < 4;i++)
	{
		m_currentXPos = ((m_matrixSize / 2) * spriteSize)
			+ (m_units[i].Get<CPieceUnit>().GetXIndex() * spriteSize)
			+ matrixStartX;
		m_currentYPos =
			(m_units[i].Get<CPieceUnit>().GetYIndex() * spriteSize)
			+ matrixStartY;
		m_units[i].Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(),
			D3DXVECTOR2(m_currentXPos, m_currentYPos), m_units[i].Get<CPieceUnit>().GetColor());
	}
}
