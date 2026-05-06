#include "Tetriminos.h"

void Tetriminos::Init(CSprite sprite, Tetrimino tetrimino)
{
	//m_pivotPoint = tetrimino.pivotPoint;
	m_matrixSize = tetrimino.pieceMatrixSize;
	m_pivotPoint.x = tetrimino.pieceMatrixSize / 2;
	m_pivotPoint.y = 0;
	m_locked = false;

	for (int i = 0;i < 4;i++)
	{
		GameObject newUnit;
		newUnit.Add<CSprite>(sprite);
		CPieceUnit newPiece = CPieceUnit(tetrimino.pieces[i].xIndex, tetrimino.pieces[i].yIndex, tetrimino.pivotPoint, tetrimino.color);
		newUnit.Add<CPieceUnit>(newPiece);
		m_units[i] = newUnit;

		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
	std::cout << "\n" << std::endl;
}

TetrminoUnits& Tetriminos::GetPieces()
{
	return m_units;
}

bool Tetriminos::IsLocked()
{
	return m_locked;
}

bool Tetriminos::BoundaryCheck(int xIndex, int yIndex)
{
	if (xIndex < m_minXIndex || xIndex > m_maxXIndex)
	{
		return false;
	}
	if (yIndex < m_minYIndex || yIndex > m_maxYIndex)
	{
		return false;
	}

	return true;
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

	int finalX[4];
	int finalY[4];
	bool isSafe = true;

	for (int i = 0; i < 4 && isSafe; i++)
	{
		CPieceUnit& unit = m_units[i].Get<CPieceUnit>();

		float x = (float)unit.GetLocalXIndex();
		float y = (float)unit.GetLocalYIndex();

		float rotatedX;
		float rotatedY;

		if (rotateDirection == CW)
		{
			rotatedX = y - (unit.GetLocalPivot().y) + (unit.GetLocalPivot().x);
			rotatedY = -x + (unit.GetLocalPivot().x) + (unit.GetLocalPivot().y);
		}
		else
		{
			rotatedX = unit.GetLocalPivot().x - (y - unit.GetLocalPivot().y);
			rotatedY = unit.GetLocalPivot().y + (x - unit.GetLocalPivot().x);
		}

		finalX[i] = (int)round(rotatedX);
		finalY[i] = (int)round(rotatedY);

		isSafe = BoundaryCheck(finalX[i] + m_pivotPoint.x, finalY[i] + m_pivotPoint.y);

		if (!isSafe)
		{
			std::cout << "Unsafe :" << finalX[i] << " | " << finalY[i] << std::endl;
		}
	}

	if (isSafe)
	{
		for (int i = 0;i < 4;i++)
		{
			m_units[i].Get<CPieceUnit>().SetLocalIndex(finalX[i], finalY[i]);

			std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
		}

		std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
		std::cout << "\n" << std::endl;
	}
}

void Tetriminos::MovePiece(int moveDirection)
{
	m_pivotPoint.x += moveDirection;

	for (int i = 0; i < 4; i++)
	{
		std::cout << m_units[i].Get<CPieceUnit>().GetXIndex(m_pivotPoint.x) << " | " << m_units[i].Get<CPieceUnit>().GetYIndex(m_pivotPoint.y) << std::endl;
	}
	std::cout << "Pivot :" << m_pivotPoint.x << " | " << m_pivotPoint.y << std::endl;
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

		m_units[i].Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(),
			D3DXVECTOR2(m_currentXPos, m_currentYPos), m_units[i].Get<CPieceUnit>().GetColor());
		//std::cout << m_units[i].Get<CPieceUnit>().GetLocalXIndex() << " | " << m_units[i].Get<CPieceUnit>().GetLocalYIndex() << std::endl;
	}
	//std::cout << "\n" << std::endl;
}
