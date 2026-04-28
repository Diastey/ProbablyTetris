#pragma once
#include <tuple>
#include <string>

enum Tag
{
	Default = 0
};

template<typename... Components>
class Entity
{
	using ComponentTuple = std::tuple<Components...>;

	size_t m_id = 0;
	ComponentTuple m_components;
	Tag m_tag = Default;
	bool m_alive = true;

public:
	Entity() = default;

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
	bool IsAlive() const { return m_alive; }
	void Destroy() { m_alive = false; }
	const Tag& GetTag() const { return m_tag; }
};

//template<typename... Components>
//template<typename T>
//T& Entity<Components...>::Get()
//{
//    return std::get<T>(m_components);
//}
//
//template<typename... Components>
//template<typename T>
//const T& Entity<Components...>::Get() const
//{
//    return std::get<T>(m_components);
//}

//template<typename... Components>
//template<typename T>
//bool Entity<Components...>::Has() const
//{
//	return std::get<T>(m_components).exists;
//}

//template<typename... Components>
//template<typename T>
//void Entity<Components...>::Remove()
//{
//	auto& component = std::get<T>(m_components);
//	component = T{};
//	component.exists = false;
//}

//template<typename... Components>
//template<typename T, typename... Args>
//T& Entity<Components...>::Add(Args&&... args)
//{
//	auto& component = std::get<T>(m_components);
//	component = T(std::forward<Args>(args)...);
//	component.exists = true;
//	return component;
//}