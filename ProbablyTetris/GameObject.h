#pragma once
#include <tuple>

#include "CTransform.h"
#include "CSprite.h"
#include "CMatrixUnit.h"
#include "CPieceUnit.h"

enum Tag
{
	Default = 0
};

using ComponentTuple = std::tuple
<
	CTransform,
	CSprite,
	CMatrixUnit
>;

class GameObject
{
	size_t m_id = 0;
	ComponentTuple m_components;
	Tag m_tag = Default;
	bool m_active = true;

public:
	GameObject() = default;

	template<typename T, typename... Args>
	T& Add(Args&&... args)
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
	void Destroy() { m_active = false; }
	const Tag& GetTag() const { return m_tag; }

	void ReleaseObject()
	{
		Get<CSprite>().Release();
	}
};