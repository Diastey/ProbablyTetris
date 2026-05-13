#pragma once
#include "UIObject.h"
#include <vector>

class Panel :public UIObject
{
	Panel* m_parentPanel = nullptr;
	std::vector<UIObject> m_uiObj;
	std::vector<Panel> m_childrenPanel;

public:
	void DrawPanel()
	{

	}

	void AddPanel(const Panel& panel)
	{
		m_childrenPanel.push_back(panel);
	}
	void AddUIObject(const UIObject& uiObj)
	{
		m_uiObj.push_back(uiObj);
	}
	bool DeactivateChildrenPanelAt(const int index)
	{
		if (index >= m_childrenPanel.size())
		{
			return false;
		}
		m_childrenPanel.at(index).Deactivate();
		return true;
	}
	bool ReactivateChildrenPanelAt(const int index)
	{
		if (index >= m_childrenPanel.size())
		{
			return false;
		}
		m_childrenPanel.at(index).Reactivate();
		return true;
	}
	bool DeactivateUIObjectAt(const int index)
	{
		if (index >= m_childrenPanel.size())
		{
			return false;
		}
		m_childrenPanel.at(index).Deactivate();
		return true;
	}
	bool ReactivateUIObjectAt(const int index)
	{
		if (index >= m_uiObj.size())
		{
			return false;
		}
		m_uiObj.at(index).Reactivate();
		return true;
	}
	void SetParentPanel(Panel& parentPanel)
	{
		m_parentPanel = &parentPanel;
	}
	const Panel& GetParentPanel()
	{
		if (m_parentPanel == nullptr)
		{
			return *this;
		}
		return *m_parentPanel;
	}
	void ReleasePanel()
	{
		for (Panel& panels : m_childrenPanel)
		{
			panels.ReleasePanel();
		}

		ReleaseObject();
	}
};