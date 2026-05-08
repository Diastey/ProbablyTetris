#include "Tetriminos.h"

void Tetriminos::Init(CSprite sprite, Tetrimino tetrimino, int matrixMiddleX)
{
	//m_pivotPoint = tetrimino.pivotPoint;
	m_matrixSize = tetrimino.pieceMatrixSize;
	m_pivotPoint.x = matrixMiddleX;
	m_pivotPoint.y = -1;
	m_locked = false;
	sprite.SetColor(tetrimino.color);

	for (int i = 0;i < 4;i++)
	{
		GameObject newUnit;
		newUnit.Set<CSprite>(sprite);
		CPieceUnit newPiece = CPieceUnit(tetrimino.pieces[i].xIndex, tetrimino.pieces[i].yIndex, tetrimino.pivotPoint);
		newUnit.Set<CPieceUnit>(newPiece);
		m_units[i] = newUnit;

		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
	std::cout << "Current Direction: " << m_currentDir << std::endl;
	std::cout << "\n" << std::endl;
}

TetrminoUnits& Tetriminos::GetPieces()
{
	return m_units;
}

Vec2f& Tetriminos::GetPivotPoint()
{
	return m_pivotPoint;
}

bool Tetriminos::IsLocked()
{
	return m_locked;
}

void Tetriminos::SetLocked(bool locked)
{
	m_locked = locked;
}

void Tetriminos::MoveLocalPieces(const int newXIndex[4], const int newYindex[4])
{
	for (int i = 0;i < 4;i++)
	{
		m_units[i].Get<CPieceUnit>().SetLocalIndex(newXIndex[i], newYindex[i]);

		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
	std::cout << "Current Direction: " << m_currentDir << std::endl;
	std::cout << "\n" << std::endl;
}

void Tetriminos::RotatePiece(RotateDir rotateDirection)
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
}

void Tetriminos::ShiftPiece(int moveDirection)
{
	m_pivotPoint.x += moveDirection;

	for (int i = 0; i < 4; i++)
	{
		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
	std::cout << "Current Direction: " << m_currentDir << std::endl;
	std::cout << "\n" << std::endl;
}

void Tetriminos::DropPiece(int amount)
{
	m_pivotPoint.y += amount;

	for (int i = 0; i < 4; i++)
	{
		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
	std::cout << "Current Direction: " << m_currentDir << std::endl;
	std::cout << "\n" << std::endl;
}

void Tetriminos::DrawPiece(int matrixStartX, int matrixStartY, int spriteSize)
{
	for (int i = 0;i < 4;i++)
	{
		m_currentXPos =
			(m_units[i].Get<CPieceUnit>().GetXIndex(std::ceill(m_pivotPoint.x)) * spriteSize)
			+ matrixStartX;
		m_currentYPos = matrixStartY
			- (m_units[i].Get<CPieceUnit>().GetYIndex(std::ceill(m_pivotPoint.y)) * spriteSize);

		m_units[i].Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), D3DXVECTOR2(m_currentXPos, m_currentYPos));
	}
}
