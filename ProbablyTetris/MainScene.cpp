#include "MainScene.h"

void MainScene::Gravity()
{
	if (m_gravityTimer.TimerCheck(m_frameTimer->GetTimePassed()))
	{
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
	}
}

void MainScene::GravityAccelerate(int& clearedRows)
{
	while (clearedRows >= m_gravityAccelerateRequirement && m_gravityTimer.GetTargetTime() > m_minGravityTime)
	{
		clearedRows -= m_gravityAccelerateRequirement;
		m_gravityTimer.AddTargetTime(-m_timerFastenAmount);
	}
}

bool MainScene::InputTimer()
{
	return m_inputTimer.TimerCheck(m_frameTimer->GetTimePassed());
}

DelayInputTypes MainScene::GetCurrentMovementInput()
{
	if (InputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		return Left;
	}
	if (InputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		return Right;
	}
	if (InputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		return Down;
	}

	return Other;
}

bool MainScene::DelaySameInput(DelayInputTypes newInput)
{
	if (m_lastInput != newInput || newInput == Other)
	{
		m_lastInput = newInput;
		m_inputTimer.ResetTimer();
	}
	else
	{
		if (!InputTimer())
		{
			m_lastInput = newInput;
			return false;
		}
		else
		{
			m_lastInput = newInput;
		}
	}

	return true;
}

void MainScene::RandSpawnNewPiece()
{
	m_tetriminoLocked = false;
	currentTetrimino = nextTetrimino;
	currentTetriminoShow = currentTetrimino;
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	m_gravityTimer.ResetTimer();
	m_inputTimer.ResetTimer();
}

void MainScene::SpawnNewPiece(int pieceNum)
{
	m_tetriminoLocked = false;
	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[pieceNum], (m_matrixCols / 2));
	currentTetriminoShow = currentTetrimino;
	m_gravityTimer.ResetTimer();
	m_inputTimer.ResetTimer();
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

void MainScene::InitiateReplayGame()
{
	m_tetriminoLocked = true;
	m_rowsToClear.clear();
	for (int i = 0;i < m_matrixRows;i++)
	{
		m_rowsToClear.push_back(i);
	}
}

void MainScene::ReplayGameFinish()
{
	lose = false;
	m_theMatrix.clear();
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

	RandSpawnNewPiece();
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

		if (!FullBoundaryCheck(finalX[i] + currentTetrimino.GetPivotPoint().x, finalY[i] + currentTetrimino.GetPivotPoint().y))
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

		if (!FullBoundaryCheck(newX, unit.GetYIndex(currentTetrimino.GetPivotPoint().y)))
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

		if (!FullBoundaryCheck(unit.GetXIndex(currentTetrimino.GetPivotPoint().x), newY))
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

		if (!UpperBoundaryCheck(y))
		{
			lose = true;
		}

		m_theMatrix[y].SetOccupiedAt(x);
		m_theMatrix[y].GetUnits()[x].Set<CSprite>(obj.Get<CSprite>());
	}

	m_rowsToClear.clear();
	m_rowsToClear = CheckRowCompleted();
	if (m_rowsToClear.size() > 0)
	{
		m_clearedRows += m_rowsToClear.size();
		m_tetriminoLocked = true;
		GravityAccelerate(m_clearedRows);
	}
	else
	{
		RandSpawnNewPiece();
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

void MainScene::MatrixClearAnimation()
{
	for (int i = 0;i < m_rowsToClear.size();i++)
	{
		m_theMatrix[m_rowsToClear[i]].GetUnits()[anim_currentLeft].Set<CSprite>(m_matrixSprite);
		m_theMatrix[m_rowsToClear[i]].GetUnits()[anim_currentRight].Set<CSprite>(m_matrixSprite);
	}
	anim_currentLeft--;
	anim_currentRight++;

	if (anim_currentLeft < 0 && anim_currentRight >(m_matrixCols - 1))
	{
		anim_currentLeft = anim_leftStart;
		anim_currentRight = anim_rightStart;
		if (!lose)
		{
			MatrixClearFinish();
		}
		else
		{
			ReplayGameFinish();
		}
	}
}

void MainScene::MatrixClearFinish()
{
	for (int i = 0;i < m_rowsToClear.size();i++)
	{
		m_theMatrix[m_rowsToClear[i]].ClearRow();
		for (int j = 0;j < m_rowsToClear[i];j++)
		{
			m_theMatrix[m_rowsToClear[i] - j].CopyRow(m_theMatrix[m_rowsToClear[i] - j - 1]);
		}
	}

	RandSpawnNewPiece();
}

bool MainScene::PieceCollidedCheck(int xIndex, int yIndex)
{
	return !GetMatrixUnitAt(xIndex, -yIndex).Get<CMatrixUnit>().IsOccupied();
}

bool MainScene::FullBoundaryCheck(int xIndex, int yIndex)
{
	if (!BorderBoundaryCheck(xIndex))
	{
		return false;
	}

	if (!BottomBoundaryCheck(yIndex))
	{
		return false;
	}

	//if (!UpperBoundaryCheck(yIndex))
	//{
	//	return false;
	//}

	//if (-yIndex < 0 || -yIndex > m_matrixRows - 1)
	//{
	//	return false;
	//}

	return true;
}

bool MainScene::BorderBoundaryCheck(int xIndex)
{
	if (xIndex < 0 || xIndex > m_matrixCols - 1)
	{
		return false;
	}
	return true;
}

bool MainScene::BottomBoundaryCheck(int yIndex)
{
	if (-yIndex > m_matrixRows - 1)
	{
		return false;
	}

	return true;
}

bool MainScene::UpperBoundaryCheck(int yIndex)
{
	if (yIndex <= deadZone)
	{
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

	// Initialize tetriminos
	srand(time(0));
	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	currentTetriminoShow = currentTetrimino;
	silhouetteTetrimino.Init(m_pieceSprite, TetriminoShapes::Silhouette, (m_matrixCols / 2));
	nextTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));

	// Initialize timers
	m_gravityTimer = Timer(m_initialGravityTIme, true);
	m_inputTimer = Timer(m_inputInterval, true);

	return true;
}

void MainScene::Update(int frames)
{
	for (int i = 0;i < frames;i++)
	{
		if (lose && !m_tetriminoLocked)
		{
			InitiateReplayGame();
			return;
		}

		if (m_tetriminoLocked && m_rowsToClear.size() > 0)
		{
			MatrixClearAnimation();
			return;
		}
	}

	if (m_tetriminoLocked)
	{
		return;
	}

	Gravity();

	// Shape testings
	if (InputManager::GetInstance()->IsKeyDown(DIK_1))
	{
		SpawnNewPiece(0);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_2))
	{
		SpawnNewPiece(1);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_3))
	{
		SpawnNewPiece(2);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_4))
	{
		SpawnNewPiece(3);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_5))
	{
		SpawnNewPiece(4);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_6))
	{
		SpawnNewPiece(5);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_7))
	{
		SpawnNewPiece(6);
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
	// Drop
	if (InputManager::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		DropPieceUntilLocked();
	}

	DelayInputTypes currentInput = GetCurrentMovementInput();

	if (!DelaySameInput(currentInput))
	{
		return;
	}

	switch (currentInput)
	{
	case Left:
		// Move left
		if (ShiftPieceAttempt(-1))
		{
			currentTetrimino.ShiftPiece(-1);
			if (-RowsUntiLocked() < 1)
			{
				m_gravityTimer.DelayCurrentTimeByPercentage(0.1);
			}
		}
		break;
	case Right:
		// Move right
		if (ShiftPieceAttempt(1))
		{
			currentTetrimino.ShiftPiece(1);
			if (-RowsUntiLocked() < 1)
			{
				m_gravityTimer.DelayCurrentTimeByPercentage(0.1);
			}
		}
		break;
	case Down:
		// Move down
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
		m_gravityTimer.ResetTimer();
		break;
	}
}

void MainScene::Render()
{
	D3DXVECTOR2 drawPosition = D3DXVECTOR2(m_matrixStartX, m_matrixStartY);
	int rowCount = 0;
	for (MatrixRow& rows : m_theMatrix)
	{
		if (rowCount > deadZone)
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

	DrawCurrentAndNextPiece();
	if (m_tetriminoLocked)
	{
		return;
	}
	DrawSilhouette();
	currentTetrimino.DrawPiece(m_matrixStartX, m_matrixStartY, m_spriteSize, deadZone);
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

void MainScene::DrawSilhouette()
{
	silhouetteTetrimino.CopyPiecesPosition(currentTetrimino);
	silhouetteTetrimino.DropPiece(RowsUntiLocked());
	silhouetteTetrimino.DrawPiece(m_matrixStartX, m_matrixStartY, m_spriteSize);
}

void MainScene::DrawCurrentAndNextPiece()
{
	currentTetriminoShow.DrawPiece(m_showCurrentTetriminoPositionX, m_showCurrentTetriminoPositionY, m_spriteSize);
	nextTetrimino.DrawPiece(m_nextTetriminoPositionX, m_nextTetriminoPositionY, m_spriteSize);
}
