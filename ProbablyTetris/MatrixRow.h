#pragma once
#include "GameObject.h"
#include <vector>

class MatrixRow
{
public:
	std::vector<GameObject> m_matrixUnits;
	int m_totalOccupied = 0;

public:
	MatrixRow() = default;
	MatrixRow(const std::vector<GameObject>& newRow)
	{
		CopyRow(newRow);
	}

	std::vector<GameObject>& GetUnits();
	void AddUnit(GameObject& newUnit);
	void SetOccupiedAt(int index);
	int RecalcTotalOccupied();
	bool RowFullyOccupied();
	void ClearRow();
	void CopyRow(const MatrixRow& newRow);
	void ReleaseMatrix();
};