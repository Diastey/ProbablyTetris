#include "MainScene.h"

void MainScene::Gravity()
{
	if (tm_gravityTimer.TimerCheck(m_frameTimer->GetTimePassed()))
	{
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
		t_currentTetrimino.CalculatePiecePosition(m_matrixStartX, m_matrixStartY, m_spriteSize);
	}
}

void MainScene::GravityAccelerate(int& clearedRows)
{
	while (clearedRows >= m_gravityAccelerateRequirement && tm_gravityTimer.GetTargetTime() > m_minGravityTime)
	{
		clearedRows -= m_gravityAccelerateRequirement;
		tm_gravityTimer.AddTargetTime(-m_timerFastenAmount);
	}
}

bool MainScene::InputTimer()
{
	return tm_inputTimer.TimerCheck(m_frameTimer->GetTimePassed());
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
	if (g_lastInput != newInput || newInput == Other)
	{
		g_lastInput = newInput;
		tm_inputTimer.ResetTimer();
	}
	else
	{
		if (!InputTimer())
		{
			g_lastInput = newInput;
			return false;
		}
		else
		{
			g_lastInput = newInput;
		}
	}

	return true;
}

void MainScene::RandSpawnNewPiece()
{
	t_tetriminoLocked = false;
	t_currentTetrimino.CopyPieces(t_nextTetrimino);
	t_currentTetriminoShow.CopyPieces(t_currentTetrimino);
	t_nextTetrimino.Init(s_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));

	RecalculatePiecesLocations();
	tm_gravityTimer.ResetTimer();
	tm_inputTimer.ResetTimer();
}

void MainScene::SpawnNewPiece(int pieceNum)
{
	t_tetriminoLocked = false;
	t_currentTetrimino.Init(s_pieceSprite, TetriminoShapes::All[pieceNum], (m_matrixCols / 2));
	t_currentTetriminoShow.CopyPieces(t_currentTetrimino);

	RecalculatePiecesLocations();
	tm_gravityTimer.ResetTimer();
	tm_inputTimer.ResetTimer();
}

MatrixRow& MainScene::GetMatrixRow(int yIndex)
{
	return g_theMatrix[yIndex];
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
	t_tetriminoLocked = true;
	g_rowsToClear.clear();
	for (int i = 0;i < m_matrixRows;i++)
	{
		g_rowsToClear.push_back(i);
	}
}

void MainScene::ReplayGameFinish()
{
	g_lose = false;
	FlushMatrix();

	RandSpawnNewPiece();
}

float MainScene::CalculateScore(int totalRowsCleared)
{
	return (m_baseScorePerRow * totalRowsCleared)
		* (m_baseScoreMultiplier + ((g_currentStreak++) * m_streakScoreMultiplier));
}

bool MainScene::RotatePieceAttempt(RotateDir rotateDirection)
{
	int finalX[4];
	int finalY[4];

	for (int i = 0; i < 4; i++)
	{
		CPieceUnit& unit = t_currentTetrimino.GetPieces()[i].Get<CPieceUnit>();

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

		if (!FullBoundaryCheck(finalX[i] + t_currentTetrimino.GetPivotPoint().x, finalY[i] + t_currentTetrimino.GetPivotPoint().y))
		{
			std::cout << "Unsafe(Boudary) :" << finalX[i] << " | " << finalY[i] << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(finalX[i] + t_currentTetrimino.GetPivotPoint().x, finalY[i] + t_currentTetrimino.GetPivotPoint().y))
		{
			std::cout << "Unsafe(Collided) :" << finalX[i] + t_currentTetrimino.GetPivotPoint().x << " | " << finalY[i] + t_currentTetrimino.GetPivotPoint().y << std::endl;
			return false;
		}
	}

	t_currentTetrimino.RotatePiece(rotateDirection);
	t_currentTetrimino.MoveLocalPieces(finalX, finalY);
	RecalculatePiecesLocations();
	return true;
}

bool MainScene::ShiftPieceAttempt(int moveDirection)
{
	for (int i = 0;i < 4;i++)
	{
		CPieceUnit& unit = t_currentTetrimino.GetPieces()[i].Get<CPieceUnit>();
		int newX = unit.GetXIndex(t_currentTetrimino.GetPivotPoint().x) + moveDirection;

		if (!FullBoundaryCheck(newX, unit.GetYIndex(t_currentTetrimino.GetPivotPoint().y)))
		{
			//std::cout << "Unsafe(Boudary) :" << newX << " | " << y << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(newX, unit.GetYIndex(t_currentTetrimino.GetPivotPoint().y)))
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
		CPieceUnit& unit = t_currentTetrimino.GetPieces()[i].Get<CPieceUnit>();
		int newY = unit.GetYIndex(t_currentTetrimino.GetPivotPoint().y) + amount;

		if (!FullBoundaryCheck(unit.GetXIndex(t_currentTetrimino.GetPivotPoint().x), newY))
		{
			//std::cout << "Unsafe(Boudary) :" << unit.GetXIndex(currentTetrimino.GetPivotPoint().x) << " | " << newY << std::endl;
			return false;
		}
		if (!PieceCollidedCheck(unit.GetXIndex(t_currentTetrimino.GetPivotPoint().x), newY))
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

	t_currentTetrimino.DropPiece(amount);
	RecalculatePiecesLocations();
	return true;
}

void MainScene::DropPieceUntilLocked()
{
	t_currentTetrimino.DropPiece(RowsUntiLocked());
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
	for (GameObject& obj : t_currentTetrimino.GetPieces())
	{
		int x = obj.Get<CPieceUnit>().GetXIndex(t_currentTetrimino.GetPivotPoint().x);
		int y = -obj.Get<CPieceUnit>().GetYIndex(t_currentTetrimino.GetPivotPoint().y);

		if (!UpperBoundaryCheck(y))
		{
			g_lose = true;
		}

		g_theMatrix[y].SetOccupiedAt(x);
		g_theMatrix[y].GetUnits()[x].Set<CSprite>(obj.Get<CSprite>());
	}

	g_rowsToClear.clear();
	g_rowsToClear = CheckRowCompleted();
	if (g_rowsToClear.size() > 0)
	{
		g_score += CalculateScore(g_rowsToClear.size());
		g_clearedRows += g_rowsToClear.size();
		t_tetriminoLocked = true;
		GravityAccelerate(g_clearedRows);
		std::cout << g_score << std::endl;
	}
	else
	{
		g_currentStreak = 0;
		RandSpawnNewPiece();
	}
}

void MainScene::RecalculatePiecesLocations()
{
	t_currentTetrimino.CalculatePiecePosition(m_matrixStartX, m_matrixStartY, m_spriteSize);
	t_currentTetriminoShow.CalculatePiecePosition(m_showCurrentTetriminoPositionX, m_showCurrentTetriminoPositionY, m_spriteSize);
	t_nextTetrimino.CalculatePiecePosition(m_nextTetriminoPositionX, m_nextTetriminoPositionY, m_spriteSize);
}

std::vector<int> MainScene::CheckRowCompleted()
{
	std::vector<int> rows;

	for (int i = 0;i < m_matrixRows;i++)
	{
		if (g_theMatrix[i].RowFullyOccupied())
		{
			rows.push_back(i);
		}
	}

	return rows;
}

void MainScene::MatrixClearAnimation()
{
	for (int i = 0;i < g_rowsToClear.size();i++)
	{
		g_theMatrix[g_rowsToClear[i]].GetUnits()[anim_currentLeft].Set<CSprite>(s_matrixSprite);
		g_theMatrix[g_rowsToClear[i]].GetUnits()[anim_currentRight].Set<CSprite>(s_matrixSprite);
	}
	anim_currentLeft--;
	anim_currentRight++;

	if (anim_currentLeft < 0 && anim_currentRight >(m_matrixCols - 1))
	{
		anim_currentLeft = anim_leftStart;
		anim_currentRight = anim_rightStart;
		if (!g_lose)
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
	FlushMatrix();

	RandSpawnNewPiece();
}

void MainScene::FlushMatrix()
{
	for (int i = 0;i < g_rowsToClear.size();i++)
	{
		for (int j = 0;j < g_rowsToClear[i];j++)
		{
			g_theMatrix[g_rowsToClear[i] - j].CopyRow(g_theMatrix[g_rowsToClear[i] - j - 1]);
		}
	}

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
	if (yIndex <= m_deadZone)
	{
		return false;
	}
	return true;
}

bool MainScene::Initialize()
{
	if (!s_matrixSprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Matrix.png"))
	{
		return false;
	}

	if (!s_pieceSprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Piece.png"))
	{
		return false;
	}

	if (!s_inputKeySprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/Keys.png"))
	{
		return false;
	}

	if (!s_specialKeySprite.InitializeSprite(DirectXManager::GetInstance()->GetD3dDevice(), "Assets/SpecialKeys.png"))
	{
		return false;
	}

	// Initialize the matrix
	D3DXVECTOR2 matrixStartPos = D3DXVECTOR2(m_matrixStartX, m_matrixStartY);
	int rowCount = 0;
	for (int i = 0;i < m_matrixRows;i++)
	{
		MatrixRow newRow = MatrixRow();
		for (int j = 0;j < m_matrixCols;j++)
		{
			GameObject matrixUnit = GameObject();
			matrixUnit.Set<CSprite>(s_matrixSprite);
			matrixUnit.Set<CMatrixUnit>(CMatrixUnit());
			matrixUnit.Set<CTransform>(CTransform(matrixStartPos));
			newRow.AddUnit(matrixUnit);
			matrixStartPos.x += m_spriteSize;
		}
		g_theMatrix.push_back(newRow);
		rowCount++;
		matrixStartPos.x = m_matrixStartX;
		matrixStartPos.y += m_spriteSize;
	}

	// Initialize UI
	UIObject testUiObj = UIObject();
	testUiObj.Set<CLabel>(CLabel(12, 32, 1, false, "Comic Sans MS", "Next Piece", 15));
	testUiObj.Get<CLabel>().InitializeLabel(DirectXManager::GetInstance()->GetD3dDevice());
	testUiObj.Get<CTransform>().SetPosition(m_nextTetriminoPositionX + ((int)testUiObj.Get<CLabel>().GetFontWidth() / 2), m_nextTetriminoPositionY - 48);
	m_screenPanel.AddUIObject(testUiObj);

	// Initialize tetriminos
	srand(time(0));
	t_currentTetrimino.Init(s_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));
	t_currentTetriminoShow.CopyPieces(t_currentTetrimino);
	//currentTetriminoShow = currentTetrimino;

	t_silhouetteTetrimino.Init(s_pieceSprite, TetriminoShapes::Silhouette, (m_matrixCols / 2));
	t_nextTetrimino.Init(s_pieceSprite, TetriminoShapes::All[rand() % 7], (m_matrixCols / 2));

	RecalculatePiecesLocations();

	// Initialize timers
	tm_gravityTimer = Timer(m_initialGravityTIme, true);
	tm_inputTimer = Timer(m_inputInterval, true);

	return true;
}

void MainScene::Update(int frames)
{
	for (int i = 0;i < frames;i++)
	{
		if (g_lose && !t_tetriminoLocked)
		{
			InitiateReplayGame();
			return;
		}

		if (t_tetriminoLocked && g_rowsToClear.size() > 0)
		{
			MatrixClearAnimation();
			return;
		}
	}

	if (t_tetriminoLocked)
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
			t_currentTetrimino.ShiftPiece(-1);
			RecalculatePiecesLocations();
			if (-RowsUntiLocked() < 1)
			{
				tm_gravityTimer.DelayCurrentTimeByPercentage(0.1);
			}
		}
		break;
	case Right:
		// Move right
		if (ShiftPieceAttempt(1))
		{
			t_currentTetrimino.ShiftPiece(1);
			RecalculatePiecesLocations();
			if (-RowsUntiLocked() < 1)
			{
				tm_gravityTimer.DelayCurrentTimeByPercentage(0.1);
			}
		}
		break;
	case Down:
		// Move down
		if (!DropPieceAttempt(-1))
		{
			PieceLocked();
		}
		tm_gravityTimer.ResetTimer();
		break;
	}
}

void MainScene::Render()
{
	m_screenPanel.DrawPanel();

	int rowCount = 0;
	for (MatrixRow& rows : g_theMatrix)
	{
		if (rowCount > m_deadZone)
		{
			for (GameObject& obj : rows.GetUnits())
			{
				obj.Get<CSprite>().DrawSprite(DirectXManager::GetInstance()->GetSpriteBrush(), obj.Get<CTransform>().GetPosition());
			}
		}
		rowCount++;
	}

	DrawCurrentAndNextPiece();
	if (t_tetriminoLocked)
	{
		return;
	}
	DrawSilhouette();
	t_currentTetrimino.DrawPiece(m_matrixStartY + (m_spriteSize * m_deadZone));
}

void MainScene::DrawSilhouette()
{
	t_silhouetteTetrimino.CopyPiecesPosition(t_currentTetrimino);
	t_silhouetteTetrimino.DropPiece(RowsUntiLocked());
	t_silhouetteTetrimino.CalculatePiecePosition(m_matrixStartX, m_matrixStartY, m_spriteSize);
	t_silhouetteTetrimino.DrawPiece();
}

void MainScene::DrawCurrentAndNextPiece()
{
	t_currentTetriminoShow.DrawPiece();
	t_nextTetrimino.DrawPiece();
}

void MainScene::Release()
{
	for (MatrixRow& rows : g_theMatrix)
	{
		rows.ReleaseMatrix();
	}
}