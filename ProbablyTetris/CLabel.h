#pragma once
#include "Component.h"
#include <string>

class CLabel :public Component
{
	std::string m_label;
public:
	CLabel()
		:m_label("")
	{

	}
	CLabel(std::string label)
		:m_label(label)
	{

	}
};

