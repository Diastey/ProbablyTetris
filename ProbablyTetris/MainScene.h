#pragma once
#include <array>

#include "BaseScene.h"
#include "MatrixRow.h"
#include "Tetriminos.h"
#include "GameWindowManager.h"

class MainScene :public BaseScene
{
	std::vector<MatrixRow> m_theMatrix;
	//Tetriminos m_tetriminos[7];

	int m_matrixRows = 22;
	int m_matrixCols = 10;
	int m_spriteSize = 32;
	CSprite m_matrixSprite = CSprite(m_spriteSize, m_spriteSize);
	CSprite m_pieceSprite = CSprite(m_spriteSize, m_spriteSize);
	int m_matrixStartX = ((GameWindowManager::GetInstance()->GetWindowWidth()) / 2) - ((m_spriteSize * m_matrixCols) / 2);
	int m_matrixStartY = ((GameWindowManager::GetInstance()->GetWindowHeight()) / 2) - ((m_spriteSize * m_matrixRows) / 2);

public:
	MainScene(int fps)
		:BaseScene(fps)
	{
	}

	bool Initialize() override;
	void Update(int frames) override;
	void Render() override;
	void Release() override;
};

