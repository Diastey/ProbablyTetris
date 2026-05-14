#pragma once

#include "BaseScene.h"
#include "MatrixRow.h"
#include "Tetriminos.h"
#include "GameWindowManager.h"
#include "Timer.h"
#include "TextFileIO.h"

#include <cstdlib>
#include <iostream>

enum DelayInputTypes
{
	Other,
	Left,
	Right,
	Down
};

class MainScene :public BaseScene
{
	// Game data
	std::vector<MatrixRow> g_theMatrix;
	std::vector<int> g_rowsToClear;
	bool g_lose = false;
	DelayInputTypes g_lastInput = Other;
	int g_clearedRows = 0;
	int g_score = 0;
	int g_currentStreak = 0;
	int g_highestScore = 0;
	std::string g_scoreText = "0";
	std::string g_streakText = "0";
	std::string g_highestScoreText = "0";

	// Tetrimino
	Tetriminos t_currentTetrimino;
	Tetriminos t_currentTetriminoShow;
	Tetriminos t_silhouetteTetrimino;
	Tetriminos t_nextTetrimino;
	bool t_tetriminoLocked = false;

	// Constants for the matrix
	const int m_deadZone = 2;
	const int m_matrixRows = 22;
	const int m_matrixCols = 10;
	const int m_spriteSize = 32;
	const int m_matrixStartX = ((GameWindowManager::GetInstance()->GetWindowWidth()) / 2) - ((m_spriteSize * m_matrixCols) / 2);
	const int m_matrixStartY = ((GameWindowManager::GetInstance()->GetWindowHeight()) / 2) - ((m_spriteSize * m_matrixRows) / 2);
	const int m_showCurrentTetriminoPositionX = m_matrixStartX;
	const int m_showCurrentTetriminoPositionY = m_matrixStartY / 2;
	const int m_nextTetriminoPositionX = m_matrixStartX + (m_matrixCols * m_spriteSize);
	const int m_nextTetriminoPositionY = (GameWindowManager::GetInstance()->GetWindowHeight() / 4) * 3;
	// For tiemrs
	const float m_initialGravityTIme = 2;
	const float m_minGravityTime = 0.4;
	const float m_timerFastenAmount = 0.2;
	const int m_gravityAccelerateRequirement = 5;
	const float m_inputInterval = 0.2;
	// For scoring
	const float m_baseScorePerRow = 100;
	const float m_baseScoreMultiplier = 1;
	const float m_multipleRowsMultiplier = 0.25;
	const float m_streakScoreMultiplier = 0.5;
	const std::string m_highScoreFileName = "highScore.txt";

	// Sprites
	CSprite s_matrixSprite = CSprite(m_spriteSize, m_spriteSize, OtherColors::SemiVisible);
	CSprite s_pieceSprite = CSprite(m_spriteSize, m_spriteSize);
	const int m_controlsUIPositionX = m_matrixStartX / 4;
	const int m_controlsUIPositionY = (GameWindowManager::GetInstance()->GetWindowHeight()) / 8;
	const int m_specialKeySpriteSheetHeight = 48;
	const int m_specialKeySpriteSheetWidth = 96;
	CSprite s_spaceKeySprite = CSprite(m_specialKeySpriteSheetHeight, m_specialKeySpriteSheetWidth);
	CSprite s_escKeySprite = CSprite(m_specialKeySpriteSheetHeight, m_specialKeySpriteSheetWidth);
	const int m_inputKeySpriteSheetHeight = 48;
	const int m_inputKeySpriteSheetWidth = 240;
	const int m_inputKeySpriteRows = 1;
	const int m_inputKeySpriteCols = 5;
	CSprite s_inputKeySprite = CSprite(m_inputKeySpriteSheetHeight, m_inputKeySpriteSheetWidth,
		m_inputKeySpriteRows, m_inputKeySpriteCols, (m_inputKeySpriteRows * m_inputKeySpriteCols), 0);

	// Timer
	Timer tm_inputTimer;
	Timer tm_gravityTimer;

	// Clear animation
	int anim_leftStart = (m_matrixCols / 2) - 1;
	int anim_rightStart = m_matrixCols / 2;
	int anim_currentLeft = anim_leftStart;
	int anim_currentRight = anim_rightStart;

	// Score UI
	const int ui_scorePanelStartX = m_matrixStartX + (m_spriteSize * m_matrixCols) + (m_matrixStartX / 5);
	const int ui_scorePanelStartY = GameWindowManager::GetInstance()->GetWindowHeight() / 4;

	// UI Font settings
	const int defaultFontWidth = 12;
	const int defaultFontHeight = 32;
	const int bigFontWidth = 16;
	const int bigFontHeight = 48;
	const float bigTextOffset = 1.5;

public:
	MainScene(int fps)
		:BaseScene(fps)
	{
	}

	// Timer Chekcs
	void Gravity();
	void GravityAccelerate(int& clearedRows);
	bool InputTimer();
	DelayInputTypes GetCurrentMovementInput();
	bool DelaySameInput(DelayInputTypes newInput);

	// The Matrix controls
	void RandSpawnNewPiece();
	void SpawnNewPiece(int pieceNum);
	MatrixRow& GetMatrixRow(int yIndex);
	GameObject& GetMatrixUnitAt(int xIndex, int yIndex);
	void SetMatrixUnitOccupied(int xIndex, int yIndex, bool occupied);

	// Current Piece controls
	bool RotatePieceAttempt(RotateDir rotateDirection);
	bool ShiftPieceAttempt(int moveDirection);
	bool PiecesSafeToDrop(int amount);
	bool DropPieceAttempt(int amount);
	void DropPieceUntilLocked();
	int RowsUntiLocked();
	void PieceLocked();
	void RecalculatePiecesLocations();

	// Clearing rows
	std::vector<int> CheckRowCompleted();
	void MatrixClearAnimation();
	void MatrixClearFinish();
	void FlushMatrix();
	void InitiateReplayGame();
	void ReplayGameFinish();
	float CalculateScore(int totalRowsCleared);

	// Checks
	bool PieceCollidedCheck(int xIndex, int yIndex);
	bool FullBoundaryCheck(int xIndex, int yIndex);
	bool BorderBoundaryCheck(int xIndex);
	bool BottomBoundaryCheck(int yIndex);
	bool UpperBoundaryCheck(int yIndex);

	void InitializeUI();
	bool Initialize() override;
	void Update(int frames) override;
	void Render() override;
	void Release() override;

	// UI
	void DrawSilhouette();
	void DrawCurrentAndNextPiece();
	void UpdateScoreText();
};