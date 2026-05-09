#include "MainScene.h"

void MainScene::AutoDrop()
{
	if (m_tetriminoTimer.TimerCheck(m_frameTimer->GetTimePassed()))
	{
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
	}
}

void MainScene::SpawnNewPiece()
{
	m_tetriminoLocked = false;
	currentTetrimino = nextTetrimino;
	currentTetriminoShow = nextTetrimino;
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
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
			//std::cout << "Unsafe(Boudary) :" << newX << " | " << y << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(newX, unit.GetYIndex(currentTetrimino.GetPivotPoint().y)))
		{
			//std::cout << "Unsafe(Collided) :" << newX << " | " << unit.GetXIndex(currentTetrimino.GetPivotPoint().y) << std::endl;
			return false;
		}
	}
	return true;
}

bool MainScene::PiecesSafeToDrop(int amount)
{
	for (int i = 0;i < 4;i++)
	{
		CPieceUnit& unit = currentTetrimino.GetPieces()[i].Get<CPieceUnit>();
		int newY = unit.GetYIndex(currentTetrimino.GetPivotPoint().y) + amount;

		if (!BoundaryCheck(unit.GetXIndex(currentTetrimino.GetPivotPoint().x), newY))
		{
			//std::cout << "Unsafe(Boudary) :" << unit.GetXIndex(currentTetrimino.GetPivotPoint().x) << " | " << newY << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(unit.GetXIndex(currentTetrimino.GetPivotPoint().x), newY))
		{
			//std::cout << "Unsafe(Collided) :" << unit.GetXIndex(currentTetrimino.GetPivotPoint().x) << " | " << newY + currentTetrimino.GetPivotPoint().y << std::endl;
			return false;
		}
	}

	return true;
}

bool MainScene::DropPieceAttempt(int amount)
{
	if (!PiecesSafeToDrop(amount))
	{
		return false;
	}

	currentTetrimino.DropPiece(amount);
	return true;
}

void MainScene::DropPieceUntilLocked()
{
	currentTetrimino.DropPiece(RowsUntiLocked());
	PieceLocked();
}

int MainScene::RowsUntiLocked()
{
	for (int i = 0;i < m_matrixRows;i++)
	{
		if (!PiecesSafeToDrop(-i - 1))
		{
			return -i;
		}
	}
	return 0;
}

void MainScene::PieceLocked()
{
	for (GameObject& obj : currentTetrimino.GetPieces())
	{
		int x = obj.Get<CPieceUnit>().GetXIndex(currentTetrimino.GetPivotPoint().x);
		int y = -obj.Get<CPieceUnit>().GetYIndex(currentTetrimino.GetPivotPoint().y);

		m_theMatrix[y].SetOccupiedAt(x);
		m_theMatrix[y].GetUnits()[x].Set<CSprite>(obj.Get<CSprite>());
	}

	m_rowsCompleted.clear();
	m_rowsCompleted = CheckRowCompleted();
	if (m_rowsCompleted.size() > 0)
	{
		m_tetriminoLocked = true;
	}
	else
	{
		SpawnNewPiece();
	}
}

std::vector<int> MainScene::CheckRowCompleted()
{
	std::vector<int> rows;

	for (int i = 0;i < m_matrixRows;i++)
	{
		if (m_theMatrix[i].RowFullyOccupied())
		{
			rows.push_back(i);
		}
	}

	return rows;
}

void MainScene::MatrixUnlockedAnimation()
{
	for (int i = 0;i < m_rowsCompleted.size();i++)
	{
		m_theMatrix[m_rowsCompleted[i]].GetUnits()[anim_currentLeft].Set<CSprite>(m_matrixSprite);
		m_theMatrix[m_rowsCompleted[i]].GetUnits()[anim_currentRight].Set<CSprite>(m_matrixSprite);
	}
	anim_currentLeft--;
	anim_currentRight++;

	if (anim_currentLeft < 0 && anim_currentRight >(m_matrixCols - 1))
	{
		MatrixUnlockFinish();
	}
}

void MainScene::MatrixUnlockFinish()
{
	m_tetriminoLocked = false;
	anim_currentLeft = anim_leftStart;
	anim_currentRight = anim_rightStart;

	for (int i = 0;i < m_rowsCompleted.size();i++)
	{
		m_theMatrix[m_rowsCompleted[i]].ClearRow();
		for (int j = 0;j < m_rowsCompleted[i];j++)
		{
			m_theMatrix[m_rowsCompleted[i] - j].CopyRow(m_theMatrix[m_rowsCompleted[i] - j - 1]);
		}
	}

	SpawnNewPiece();
}

bool MainScene::PieceCollidedCheck(int xIndex, int yIndex)
{
	return !GetMatrixUnitAt(xIndex, -yIndex).Get<CMatrixUnit>().IsOccupied();
}

bool MainScene::BoundaryCheck(int xIndex, int yIndex)
{
	if (xIndex < 0 || xIndex > m_matrixCols - 1)
	{
		//std::cout << "Boundary X: " << xIndex << std::endl;
		return false;
	}
	if (-yIndex < 0 || -yIndex > m_matrixRows - 1)
	{
		//std::cout << "Boundary Y: " << -yIndex << std::endl;
		return false;
	}

	return true;
}

bool MainScene::UpperBoundaryCheck(int xIndex, int yIndex)
{
	if (xIndex < 0 || xIndex > m_matrixCols - 1)
	{
		//std::cout << "Boundary X: " << xIndex << std::endl;
		return false;
	}
	if (-yIndex < 0 || -yIndex > m_matrixRows - 1)
	{
		//std::cout << "Boundary Y: " << -yIndex << std::endl;
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
			matrixUnit.Set<CSprite>(m_matrixSprite);
			matrixUnit.Set<CMatrixUnit>(CMatrixUnit());
			newRow.AddUnit(matrixUnit);
		}
		m_theMatrix.push_back(newRow);
	}

	srand(time(0));
	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	currentTetriminoShow = currentTetrimino;
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	m_tetriminoTimer = Timer(m_initialTimer);

	return true;
}

void MainScene::Update(int frames)
{
	AutoDrop();

	if (m_tetriminoLocked && m_rowsCompleted.size() > 0)
	{
		MatrixUnlockedAnimation();
		return;
	}

	if (m_tetriminoLocked)
	{
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
		//if (!DropPieceAttempt(1))
		//{
		//	PieceLocked();
		//}
	}
	// Move down
	if (InputManager::GetInstance()->IsKeyDown(DIK_S))
	{
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
			m_tetriminoTimer.ResetTimer();
		}
	}
	// Move left
	if (InputManager::GetInstance()->IsKeyDown(DIK_A))
	{
		if (ShiftPieceAttempt(-1))
		{
			currentTetrimino.ShiftPiece(-1);
		}
	}
	// Move right
	if (InputManager::GetInstance()->IsKeyDown(DIK_D))
	{
		if (ShiftPieceAttempt(1))
		{
			currentTetrimino.ShiftPiece(1);
		}
	}
	// Drop
	if (InputManager::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		DropPieceUntilLocked();
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
	int rowCount = 0;
	for (MatrixRow& rows : m_theMatrix)
	{
		if (rowCount > ignoreRow)
		{
			for (GameObject& obj : rows.GetUnits())
			{
				obj.Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), drawPosition);
				drawPosition.x += m_spriteSize;
			}
		}
		rowCount++;
		drawPosition.x = m_matrixStartX;
		drawPosition.y += m_spriteSize;
	}

	currentTetrimino.DrawPiece(m_matrixStartX, m_matrixStartY, m_spriteSize, false);
	currentTetriminoShow.DrawPiece(m_showCurrentTetriminoPositionX, m_showCurrentTetriminoPositionY, m_spriteSize, true);
	nextTetrimino.DrawPiece(m_nextTetriminoPositionX, m_nextTetriminoPositionY, m_spriteSize, true);
}

void MainScene::Release()
{
	for (int i = 0;i < m_gameObjects.size();i++)
	{
		m_gameObjects[i].ReleaseObject();
	}
	for (MatrixRow& rows : m_theMatrix)
	{
		rows.ReleaseMatrix();
	}
}
