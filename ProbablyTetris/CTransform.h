#pragma once
#include "Component.h"
#include <d3dx9.h>
#include <d3dx9math.h>

class CTransform : public Component
{
public:
	D3DXVECTOR2 m_scaling;
	float m_rotation;
	D3DXVECTOR2 m_position;

public:
	CTransform()
		:m_scaling(D3DXVECTOR2(1, 1)), m_rotation(0), m_position(D3DXVECTOR2(0, 0))
	{
	}
	CTransform(D3DXVECTOR2 scaling, float rotation, D3DXVECTOR2 position)
		:m_scaling(scaling), m_rotation(rotation), m_position(position)
	{
	}
	CTransform(D3DXVECTOR2 position)
		:m_scaling(D3DXVECTOR2(1, 1)), m_rotation(0), m_position(position)
	{
	}

	D3DXVECTOR2& GetPosition();
	float GetRotation();
	D3DXVECTOR2& GetScaling();
	void SetPosition(D3DXVECTOR2 newPosition);
	void SetPosition(int x, int y);
	void SetPosition(float x, float y);
};