#pragma once

#include "BaseScene.h"
#include "MatrixRow.h"
#include "Tetriminos.h"
#include "GameWindowManager.h"
#include "Timer.h"

#include <cstdlib>
#include <iostream>

class MainScene :public BaseScene
{
	std::vector<MatrixRow> m_theMatrix;
	std::vector<int> m_rowsCompleted;

	// Constants
	const int m_matrixRows = 22;
	const int m_matrixCols = 10;
	const int m_spriteSize = 32;
	const float m_initialTimer = 1.5;
	const float m_minTimer = 0.5;
	const float m_timerFastenAmount = 0.1;
	const int m_timerFastenRequirement = 5;
	const int ignoreRow = 2;
	const int m_matrixStartX = ((GameWindowManager::GetInstance()->GetWindowWidth()) / 2) - ((m_spriteSize * m_matrixCols) / 2);
	const int m_matrixStartY = ((GameWindowManager::GetInstance()->GetWindowHeight()) / 2) - ((m_spriteSize * m_matrixRows) / 2);
	const int m_showCurrentTetriminoPositionX = m_matrixStartX;
	const int m_showCurrentTetriminoPositionY = m_matrixStartY / 2;
	const int m_nextTetriminoPositionX = m_matrixStartX + (m_matrixCols * m_spriteSize);
	const int m_nextTetriminoPositionY = GameWindowManager::GetInstance()->GetWindowHeight() / 2;

	// Sprites
	CSprite m_matrixSprite = CSprite(m_spriteSize, m_spriteSize, { 155,155,155 });
	CSprite m_pieceSprite = CSprite(m_spriteSize, m_spriteSize);

	// Tetrimino
	Tetriminos currentTetrimino;
	Tetriminos currentTetriminoShow;
	Tetriminos nextTetrimino;
	bool m_tetriminoLocked = false;

	// Timer
	Timer m_tetriminoTimer;

	// Cleared animation
	int anim_leftStart = (m_matrixCols / 2) - 1;
	int anim_rightStart = m_matrixCols / 2;
	int anim_currentLeft = anim_leftStart;
	int anim_currentRight = anim_rightStart;

	// Testing
	int x = 0;
	int y = 0;
public:
	MainScene(int fps)
		:BaseScene(fps)
	{
	}

	void AutoDrop();
	void SpawnNewPiece();
	MatrixRow& GetMatrixRow(int yIndex);
	GameObject& GetMatrixUnitAt(int xIndex, int yIndex);
	void SetMatrixUnitOccupied(int xIndex, int yIndex, bool occupied);

	bool RotatePieceAttempt(RotateDir rotateDirection);
	bool ShiftPieceAttempt(int moveDirection);
	bool PiecesSafeToDrop(int amount);
	bool DropPieceAttempt(int amount);
	void DropPieceUntilLocked();
	int RowsUntiLocked();
	void PieceLocked();
	std::vector<int> CheckRowCompleted();

	void MatrixUnlockedAnimation();
	void MatrixUnlockFinish();

	bool PieceCollidedCheck(int xIndex, int yIndex);
	bool BoundaryCheck(int xIndex, int yIndex);
	bool BorderBoundaryCheck(int xIndex, int yIndex);
	bool BottomBoundaryCheck(int xIndex, int yIndex);
	bool UpperBoundaryCheck(int xIndex, int yIndex);

	bool Initialize() override;
	void Update(int frames) override;
	void Render() override;
	void Release() override;
};

//m_tetriminos[0].Init(m_pieceSprite, TetriminoShapes::I);
//m_tetriminos[1].Init(m_pieceSprite, TetriminoShapes::J);
//m_tetriminos[2].Init(m_pieceSprite, TetriminoShapes::L);
//m_tetriminos[3].Init(m_pieceSprite, TetriminoShapes::O);
//m_tetriminos[4].Init(m_pieceSprite, TetriminoShapes::S);
//m_tetriminos[5].Init(m_pieceSprite, TetriminoShapes::T);
//m_tetriminos[6].Init(m_pieceSprite, TetriminoShapes::Z);
