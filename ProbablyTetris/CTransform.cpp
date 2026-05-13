#include "CTransform.h"

D3DXVECTOR2 &CTransform::GetPosition()
{
	return m_position;
}

float CTransform::GetRotation()
{
	return m_rotation;
}

D3DXVECTOR2 &CTransform::GetScaling()
{
	return m_scaling;
}

void CTransform::SetPosition(D3DXVECTOR2 newPosition)
{
	m_position = newPosition;
}

void CTransform::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}


void CTransform::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}
