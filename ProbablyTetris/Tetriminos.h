#pragma once
#include "CPieceUnit.h"
#include "GameObject.h"
#include "TetriminosShapeUtil.h"
#include "DirectXManager.h"
#include "GameWindowManager.h"
#include <array>

#include <iostream>

using TetrminoUnits = GameObject[4];
enum CurrentDir
{
	TOP = 0,
	RIGHT = 1,
	BOTTOM = 2,
	LEFT = 3
};
enum RotateDir
{
	CW = 0,
	CCW = 1
};

class Tetriminos
{
	TetrminoUnits m_units;
	Vec2f m_pivotPoint = { 0,0 };
	int m_matrixSize = 0;
	CurrentDir m_currentDir = TOP;

	bool m_locked = true;

	int m_currentXPos = 0;
	int m_currentYPos = 0;

	int m_minXIndex = 0;
	int m_maxXIndex = 9;
	int m_minYIndex = -21;
	int m_maxYIndex = 0;

public:
	Tetriminos() = default;

	void Init(CSprite sprite, Tetrimino tetrimino);
	TetrminoUnits& GetPieces();
	bool IsLocked();
	bool BoundaryCheck(int xIndex, int yIndex);
	void RotatePiece(RotateDir rotateDirection);
	void MovePiece(int moveDirection);
	void DropPiece(int amount);
	void DrawPiece(int matrixStartX, int matrixStartY, int spriteSize);
};