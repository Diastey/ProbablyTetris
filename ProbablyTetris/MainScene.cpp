#include "MainScene.h"

void MainScene::SpawnNewPiece()
{
	currentTetrimino = nextTetrimino;
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	//currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[0], (m_matrixCols / 2));
}

MatrixRow& MainScene::GetMatrixRow(int yIndex)
{
	return m_theMatrix[yIndex];
}

GameObject& MainScene::GetMatrixUnitAt(int xIndex, int yIndex)
{
	return (GetMatrixRow(yIndex).GetUnits())[xIndex];
}

void MainScene::SetMatrixUnitOccupied(int xIndex, int yIndex, bool occupied)
{
	GetMatrixUnitAt(xIndex, yIndex).Get<CMatrixUnit>().SetOccupied(occupied);
}

bool MainScene::RotatePieceAttempt(RotateDir rotateDirection)
{
	int finalX[4];
	int finalY[4];

	for (int i = 0; i < 4; i++)
	{
		CPieceUnit& unit = currentTetrimino.GetPieces()[i].Get<CPieceUnit>();

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

		if (!BoundaryCheck(finalX[i] + currentTetrimino.GetPivotPoint().x, finalY[i] + currentTetrimino.GetPivotPoint().y))
		{
			std::cout << "Unsafe(Boudary) :" << finalX[i] << " | " << finalY[i] << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(finalX[i] + currentTetrimino.GetPivotPoint().x, finalY[i] + currentTetrimino.GetPivotPoint().y))
		{
			std::cout << "Unsafe(Collided) :" << finalX[i] + currentTetrimino.GetPivotPoint().x << " | " << finalY[i] + currentTetrimino.GetPivotPoint().y << std::endl;
			return false;
		}
	}

	currentTetrimino.RotatePiece(rotateDirection);
	currentTetrimino.MoveLocalPieces(finalX, finalY);
	return true;
}

bool MainScene::ShiftPieceAttempt(int moveDirection)
{
	for (int i = 0;i < 4;i++)
	{
		CPieceUnit& unit = currentTetrimino.GetPieces()[i].Get<CPieceUnit>();
		int newX = unit.GetXIndex(currentTetrimino.GetPivotPoint().x) + moveDirection;

		if (!BoundaryCheck(newX, unit.GetYIndex(currentTetrimino.GetPivotPoint().y)))
		{
			std::cout << "Unsafe(Boudary) :" << newX << " | " << y << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(newX, unit.GetYIndex(currentTetrimino.GetPivotPoint().y)))
		{
			std::cout << "Unsafe(Collided) :" << newX << " | " << unit.GetXIndex(currentTetrimino.GetPivotPoint().y) << std::endl;
			return false;
		}
	}

	currentTetrimino.ShiftPiece(moveDirection);
	return true;
}

bool MainScene::DropPieceAttempt(int amount)
{
	for (int i = 0;i < 4;i++)
	{
		CPieceUnit& unit = currentTetrimino.GetPieces()[i].Get<CPieceUnit>();
		int newY = unit.GetYIndex(currentTetrimino.GetPivotPoint().y) + amount;

		if (!BoundaryCheck(unit.GetXIndex(currentTetrimino.GetPivotPoint().x), newY))
		{
			std::cout << "Unsafe(Boudary) :" << unit.GetXIndex(currentTetrimino.GetPivotPoint().x) << " | " << newY << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(unit.GetXIndex(currentTetrimino.GetPivotPoint().x), newY))
		{
			std::cout << "Unsafe(Collided) :" << unit.GetXIndex(currentTetrimino.GetPivotPoint().x) << " | " << newY + currentTetrimino.GetPivotPoint().y << std::endl;
			return false;
		}
	}

	currentTetrimino.DropPiece(amount);
	return true;
}

void MainScene::PieceLocked()
{
	for (GameObject& obj : currentTetrimino.GetPieces())
	{
		int x = obj.Get<CPieceUnit>().GetXIndex(currentTetrimino.GetPivotPoint().x);
		int y = -obj.Get<CPieceUnit>().GetYIndex(currentTetrimino.GetPivotPoint().y);

		m_theMatrix[y].GetUnits()[x].Get<CMatrixUnit>().SetOccupied(true);
		m_theMatrix[y].GetUnits()[x].Set<CSprite>(obj.Get<CSprite>());
	}

	SpawnNewPiece();
}

void MainScene::MatrixUnlocked(int rowIndex)
{
}

bool MainScene::PieceCollidedCheck(int xIndex, int yIndex)
{
	return !GetMatrixUnitAt(xIndex, -yIndex).Get<CMatrixUnit>().IsOccupied();
}

bool MainScene::BoundaryCheck(int xIndex, int yIndex)
{
	if (xIndex < 0 || xIndex > m_matrixCols - 1)
	{
		std::cout << "Boundary X: " << xIndex << std::endl;
		return false;
	}
	if (-yIndex < 0 || -yIndex > m_matrixRows - 1)
	{
		std::cout << "Boundary Y: " << -yIndex << std::endl;
		return false;
	}

	return true;
}

bool MainScene::Initialize()
{
	if (!m_matrixSprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Matrix.png"))
	{
		return false;
	}

	if (!m_pieceSprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Piece.png"))
	{
		return false;
	}

	for (int i = 0;i < m_matrixRows;i++)
	{
		MatrixRow newRow = MatrixRow();
		for (int j = 0;j < m_matrixCols;j++)
		{
			GameObject matrixUnit = GameObject();
			matrixUnit.Set<CSprite>(CSprite(m_matrixSprite));
			matrixUnit.Set<CMatrixUnit>(CMatrixUnit());
			newRow.AddUnit(matrixUnit);
		}
		m_theMatrix.push_back(newRow);
	}

	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	//SpawnNewPiece();

	return true;
}

void MainScene::Update(int frames)
{
	if (currentTetrimino.IsLocked())
	{
		std::cout << "Locked" << std::endl;
		return;
	}

	// Rotate counter clock-wise
	if (InputManager::GetInstance()->IsKeyDown(DIK_Q))
	{
		RotatePieceAttempt(CCW);
	}
	// Rotate clock-wise
	if (InputManager::GetInstance()->IsKeyDown(DIK_E))
	{
		RotatePieceAttempt(CW);
	}
	// Mirror rotate
	if (InputManager::GetInstance()->IsKeyDown(DIK_W))
	{
		if (!DropPieceAttempt(1))
		{
			PieceLocked();
		}
	}
	// Move down
	if (InputManager::GetInstance()->IsKeyDown(DIK_S))
	{
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
	}
	// Move left
	if (InputManager::GetInstance()->IsKeyDown(DIK_A))
	{
		ShiftPieceAttempt(-1);
	}
	// Move right
	if (InputManager::GetInstance()->IsKeyDown(DIK_D))
	{
		ShiftPieceAttempt(1);
	}
	// Drop
	if (InputManager::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		SpawnNewPiece();
	}

	// Shape testings
	if (InputManager::GetInstance()->IsKeyDown(DIK_1))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[0], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_2))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[1], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_3))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[2], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_4))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[3], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_5))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[4], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_6))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[5], (m_matrixCols / 2));
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_7))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[6], (m_matrixCols / 2));
	}
}

void MainScene::Render()
{
	D3DXVECTOR2 drawPosition = D3DXVECTOR2(m_matrixStartX, m_matrixStartY);
	for (MatrixRow& rows : m_theMatrix)
	{
		for (GameObject& obj : rows.GetUnits())
		{
			obj.Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), drawPosition);
			drawPosition.x += m_spriteSize;
		}
		drawPosition.x = m_matrixStartX;
		drawPosition.y += m_spriteSize;
	}

	currentTetrimino.DrawPiece(m_matrixStartX, m_matrixStartY, m_spriteSize);

	//std::cout << m_matrixStartX << " | " << m_matrixStartY << std::endl;
	//m_tetriminos[5].DrawPiece(m_matrixStartX, m_matrixStartY, m_spriteSize);

	//for (int i = 0;i < 4;i++)
	//{
	//	m_tetriminos[0].GetPieces()[i].Get<CSprite>().DrawSprite(m_currentFrame, DirectXManager::GetInstance()->GetSpriteBrush(),
	//		D3DXVECTOR2(0 + m_tetriminos[0].GetPieces()[i].Get<CPieceUnit>().GetXIndex(), 0 + m_tetriminos[0].GetPieces()[i].Get<CPieceUnit>().GetYIndex()),
	//		m_tetriminos[0].GetPieces()[i].Get<CPieceUnit>().GetColor().R, m_tetriminos[0].GetPieces()[i].Get<CPieceUnit>().GetColor().G, m_tetriminos[0].GetPieces()[i].Get<CPieceUnit>().GetColor().B);
	//}
}

void MainScene::Release()
{
	for (int i = 0;i < m_gameObjects.size();i++)
	{
		m_gameObjects[i].ReleaseObject();
	}
	for (int i = 0;i < m_theMatrix.size();i++)
	{
		m_theMatrix[i].ReleaseMatrix();
	}
}
