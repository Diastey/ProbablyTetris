#include "Tetriminos.h"

void Tetriminos::Init(CSprite sprite, Tetrimino tetrimino, int matrixMiddleX)
{
	m_matrixSize = tetrimino.pieceMatrixSize;
	m_pivotPoint.x = matrixMiddleX;
	m_pivotPoint.y = -1;
	sprite.SetColor(tetrimino.color);

	for (int i = 0;i < 4;i++)
	{
		m_units[i].Set<CSprite>(sprite);
		CPieceUnit newPiece = CPieceUnit(tetrimino.pieces[i].x, tetrimino.pieces[i].y, tetrimino.pivotPoint);
		m_units[i].Set<CPieceUnit>(newPiece);
	}
}

TetrminoUnits& Tetriminos::GetPieces()
{
	return m_units;
}

Vec2f& Tetriminos::GetPivotPoint()
{
	return m_pivotPoint;
}

void Tetriminos::CopyPiecesPosition(Tetriminos& tetriminoToCopy)
{
	m_pivotPoint.x = tetriminoToCopy.GetPivotPoint().x;
	m_pivotPoint.y = tetriminoToCopy.GetPivotPoint().y;
	m_matrixSize = tetriminoToCopy.m_matrixSize;
	for (int i = 0;i < 4;i++)
	{
		m_units[i].Get<CPieceUnit>().SetLocalIndex(tetriminoToCopy.GetPieces()[i].Get<CPieceUnit>().GetLocalXIndex(), tetriminoToCopy.GetPieces()[i].Get<CPieceUnit>().GetLocalYIndex());
	}
}

void Tetriminos::CopyPieces(Tetriminos& tetriminoToCopy)
{
	m_pivotPoint.x = tetriminoToCopy.GetPivotPoint().x;
	m_pivotPoint.y = tetriminoToCopy.GetPivotPoint().y;
	m_matrixSize = tetriminoToCopy.m_matrixSize;
	for (int i = 0;i < 4;i++)
	{
		m_units[i].Get<CPieceUnit>().SetLocalIndex(tetriminoToCopy.GetPieces()[i].Get<CPieceUnit>().GetLocalXIndex(), tetriminoToCopy.GetPieces()[i].Get<CPieceUnit>().GetLocalYIndex());
		m_units[i].Get<CPieceUnit>().SetLocalPivot(tetriminoToCopy.GetPieces()[i].Get<CPieceUnit>().GetLocalPivot());
		m_units[i].Set<CSprite>(tetriminoToCopy.m_units[i].Get<CSprite>());
	}
}

void Tetriminos::MoveLocalPieces(const int newXIndex[4], const int newYindex[4])
{
	for (int i = 0;i < 4;i++)
	{
		m_units[i].Get<CPieceUnit>().SetLocalIndex(newXIndex[i], newYindex[i]);
	}
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
}

void Tetriminos::DropPiece(int amount)
{
	m_pivotPoint.y += amount;
}

void Tetriminos::DrawPiece(int rowsToIgnore)
{
	for (int i = 0;i < 4;i++)
	{
		if (m_units[i].Get<CTransform>().GetPosition().y > rowsToIgnore)
		{
			m_units[i].Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), m_units[i].Get<CTransform>().GetPosition());
		}
	}
}

void Tetriminos::DrawPiece()
{
	for (int i = 0;i < 4;i++)
	{
		m_units[i].Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), m_units[i].Get<CTransform>().GetPosition());
	}
}

void Tetriminos::CalculatePiecePosition(int matrixStartX, int matrixStartY, int spriteSize)
{
	for (int i = 0;i < 4;i++)
	{
		int x = matrixStartX + (m_units[i].Get<CPieceUnit>().GetXIndex(std::ceill(m_pivotPoint.x)) * spriteSize);
		int y = matrixStartY - (m_units[i].Get<CPieceUnit>().GetYIndex(std::ceill(m_pivotPoint.y)) * spriteSize);
		m_units[i].Get<CTransform>().SetPosition(x, y);
	}
}