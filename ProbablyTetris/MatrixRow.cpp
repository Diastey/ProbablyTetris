#include "MatrixRow.h"

std::vector<GameObject>& MatrixRow::GetUnits()
{
	return m_matrixUnits;
}

void MatrixRow::AddUnit(GameObject& newUnit)
{
	m_matrixUnits.push_back(newUnit);
}

void MatrixRow::SetOccupied(int index)
{
	m_matrixUnits[index].Get<CMatrixUnit>().SetOccupied(true);
}

int MatrixRow::TotalOccupied()
{
	int totalOccupied = 0;
	for (GameObject& unit : m_matrixUnits)
	{
		if (unit.Get<CMatrixUnit>().IsOccupied())
		{
			totalOccupied++;
		}
	}
	return totalOccupied;
}

bool MatrixRow::RowOccupied()
{
	return TotalOccupied() == m_matrixUnits.size();
}

void MatrixRow::ClearRow()
{
	m_matrixUnits.clear();
}

void MatrixRow::CopyRow(const std::vector<GameObject>& newRow)
{
	m_matrixUnits = newRow;
}

void MatrixRow::ReleaseMatrix()
{
	for (int i = 0;i < m_matrixUnits.size();i++)
	{
		m_matrixUnits[i].ReleaseObject();
	}
}
