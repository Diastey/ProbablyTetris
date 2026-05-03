#pragma once
#include "Component.h"

class CMatrixUnit :public Component
{
	bool m_occupied = false;
public:
	CMatrixUnit()
		:m_occupied(false)
	{
	}

	bool IsOccupied();
	void SetOccupied(bool occupied);
};

