#include "MainScene.h"

void MainScene::SpawnNewPiece()
{
	//currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[rand() % 7]);
	currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[0]);
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
	if (InputManager::GetInstance()->IsKeyDown(DIK_Q))
	{
		currentTetrimino.RotatePiece(CCW);
	}
	// Rotate clock-wise
	if (InputManager::GetInstance()->IsKeyDown(DIK_E))
	{
		currentTetrimino.RotatePiece(CW);
	}
	// Mirror rotate
	if (InputManager::GetInstance()->IsKeyDown(DIK_W))
	{
		currentTetrimino.DropPiece(1);
	}
	// Move down
	if (InputManager::GetInstance()->IsKeyDown(DIK_S))
	{
		currentTetrimino.DropPiece(-1);
	}
	// Move left
	if (InputManager::GetInstance()->IsKeyDown(DIK_A))
	{
		currentTetrimino.MovePiece(-1);
	}
	// Move right
	if (InputManager::GetInstance()->IsKeyDown(DIK_D))
	{
		currentTetrimino.MovePiece(1);
	}
	// Drop
	if (InputManager::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		SpawnNewPiece();
	}

	// Shape testings
	if (InputManager::GetInstance()->IsKeyDown(DIK_1))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[0]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_2))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[1]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_3))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[2]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_4))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[3]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_5))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[4]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_6))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[5]);
	}
	if (InputManager::GetInstance()->IsKeyDown(DIK_7))
	{
		currentTetrimino.Init(m_pieceSprite, TetriminoShapes::All[6]);
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
