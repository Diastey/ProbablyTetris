#pragma once
#include "Component.h"

class CButton :public Component
{
	bool m_clickable = true;
public:
	CButton()
	{

	}
	CButton(bool clickable)
		:m_clickable(clickable)
	{

	}
};

