#include "CMatrixUnit.h"

bool CMatrixUnit::IsOccupied()
{
	return m_occupied;
}

void CMatrixUnit::SetOccupied(bool occupied)
{
	this->m_occupied = occupied;
}
