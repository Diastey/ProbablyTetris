#include "MainScene.h"

#include <iostream>

void MainScene::SpawnNewPiece()
{
	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7]);
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
			matrixUnit.Add<CSprite>(CSprite(m_matrixSprite));
			matrixUnit.Add<CMatrixUnit>(CMatrixUnit());
			newRow.AddUnit(matrixUnit);
		}
		m_theMatrix.push_back(newRow);
	}

	SpawnNewPiece();

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
	if (InputManager::GetInstance()->IsKeyPressed(DIK_Q))
	{

	}
	// Rotate clock-wise
	if (InputManager::GetInstance()->IsKeyPressed(DIK_E))
	{

	}
	// Mirror rotate
	if (InputManager::GetInstance()->IsKeyPressed(DIK_W))
	{

	}
	// Move left
	if (InputManager::GetInstance()->IsKeyPressed(DIK_A))
	{

	}
	// Move right
	if (InputManager::GetInstance()->IsKeyPressed(DIK_D))
	{

	}
	// Move down
	if (InputManager::GetInstance()->IsKeyPressed(DIK_S))
	{

	}
	// Drop
	if (InputManager::GetInstance()->IsKeyPressed(DIK_SPACE))
	{
		SpawnNewPiece();
	}
}

void MainScene::Render()
{
	D3DXVECTOR2 drawPosition = D3DXVECTOR2(m_matrixStartX, m_matrixStartY);
	for (MatrixRow& rows : m_theMatrix)
	{
		for (GameObject& obj : rows.GetUnits())
		{
			obj.Get<CSprite>().DrawSprite(m_currentFrame, DirectXManager::GetInstance()->GetSpriteBrush(), drawPosition, 155, 155, 155);
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
