#include "MatrixRow.h"

std::vector<GameObject>& MatrixRow::GetUnits()
{
	return m_matrixUnits;
}

void MatrixRow::AddUnit(GameObject& newUnit)
{
	m_matrixUnits.push_back(newUnit);
}

void MatrixRow::SetOccupiedAt(int index)
{
	m_matrixUnits[index].Get<CMatrixUnit>().SetOccupied(true);
	m_totalOccupied++;
}

int MatrixRow::RecalcTotalOccupied()
{
	m_totalOccupied = 0;
	for (GameObject& unit : m_matrixUnits)
	{
		if (unit.Get<CMatrixUnit>().IsOccupied())
		{
			m_totalOccupied++;
		}
	}
	return m_totalOccupied;
}

bool MatrixRow::RowFullyOccupied()
{
	return m_totalOccupied == m_matrixUnits.size();
}

void MatrixRow::ClearRow()
{
	m_matrixUnits.clear();
	m_totalOccupied = 0;
}

void MatrixRow::CopyRow(const MatrixRow& newRow)
{
	m_totalOccupied = newRow.m_totalOccupied;
	for (int i = 0;i < newRow.m_matrixUnits.size();i++)
	{
		m_matrixUnits[i].Set<CSprite>(newRow.m_matrixUnits[i].Get<CSprite>());
		m_matrixUnits[i].Set<CMatrixUnit>(newRow.m_matrixUnits[i].Get<CMatrixUnit>());
	}
}

void MatrixRow::ReleaseMatrix()
{
	for (int i = 0;i < m_matrixUnits.size();i++)
	{
		m_matrixUnits[i].ReleaseObject();
	}
}
