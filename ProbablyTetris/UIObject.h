#pragma once
#include <tuple>

#include "CTransform.h"
#include "CSprite.h"
#include "CLabel.h"

using UIComponentTuple = std::tuple
<
	CTransform,
	CSprite,
	CLabel
>;

class UIObject
{
	size_t m_id = 0;
	UIComponentTuple m_components;
	Tag m_tag = Default;
	bool m_active = true;

public:
	UIObject()
		:m_id(0)
	{

	}
	UIObject(int& id)
		:m_id(id++)
	{

	}
	~UIObject() = default;

	template<typename T, typename... Args>
	T& Set(Args&&... args)
	{
		auto& component = std::get<T>(m_components);
		component = T(std::forward<Args>(args)...);
		component.exists = true;
		return component;
	}

	template<typename T>
	T& Get()
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	const T& Get() const
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	bool Has() const
	{
		return std::get<T>(m_components).exists;
	}

	template<typename T>
	void Remove()
	{
		auto& component = std::get<T>(m_components);
		component = T{};
		component.exists = false;
	}

	size_t Id() const { return m_id; }
	bool IsAlive() const { return m_active; }
	void Deactivate() { m_active = false; }
	void Reactivate() { m_active = true; }
	const Tag& GetTag() const { return m_tag; }

	void ReleaseObject()
	{
		if (Has<CSprite>())
			Get<CSprite>().Release();
		if (Has<CLabel>())
			Get<CLabel>().ReleaseLabel();
	}
};