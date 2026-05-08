#pragma once

#include "BaseScene.h"
#include "MatrixRow.h"
#include "Tetriminos.h"
#include "GameWindowManager.h"
#include <cstdlib>

#include <iostream>

class MainScene :public BaseScene
{
	std::vector<MatrixRow> m_theMatrix;

	const int m_matrixRows = 22;
	const int m_matrixCols = 10;
	const int m_spriteSize = 32;
	const int m_matrixStartX = ((GameWindowManager::GetInstance()->GetWindowWidth()) / 2) - ((m_spriteSize * m_matrixCols) / 2);
	const int m_matrixStartY = ((GameWindowManager::GetInstance()->GetWindowHeight()) / 2) - ((m_spriteSize * m_matrixRows) / 2);
	CSprite m_matrixSprite = CSprite(m_spriteSize, m_spriteSize, { 155,155,155 });
	CSprite m_pieceSprite = CSprite(m_spriteSize, m_spriteSize);

	Tetriminos currentTetrimino;
	Tetriminos nextTetrimino;

	// Testing
	int x = 0;
	int y = 0;
public:
	MainScene(int fps)
		:BaseScene(fps)
	{
	}

	void SpawnNewPiece();
	MatrixRow& GetMatrixRow(int yIndex);
	GameObject& GetMatrixUnitAt(int xIndex, int yIndex);
	void SetMatrixUnitOccupied(int xIndex, int yIndex, bool occupied);

	bool RotatePieceAttempt(RotateDir rotateDirection);
	bool ShiftPieceAttempt(int moveDirection);
	bool DropPieceAttempt(int amount);
	void PieceLocked();
	void MatrixUnlocked(int rowIndex);

	bool PieceCollidedCheck(int xIndex, int yIndex);
	bool BoundaryCheck(int xIndex, int yIndex);

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
