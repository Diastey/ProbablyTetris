#pragma once
#include "GameObject.h"
#include <vector>

class MatrixRow
{
	std::vector<GameObject> m_matrixUnits;

public:
	MatrixRow() = default;
	MatrixRow(const std::vector<GameObject>& newRow)
	{
		CopyRow(newRow);
	}

	std::vector<GameObject>& GetUnits();
	void AddUnit(GameObject& newUnit);
	void SetOccupied(int index);
	int TotalOccupied();
	bool RowOccupied();
	void ClearRow();
	void CopyRow(const std::vector<GameObject>& newRow);
	void ReleaseMatrix();
};