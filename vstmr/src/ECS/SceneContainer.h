#pragma once

#include "ECS.h"
#include "diagnostics/Logger.h"

namespace vstmr {

	class SceneContainer
	{
	public:
		SceneContainer();
		virtual ~SceneContainer() = default;

	public:
		template<class T, class... Args>
		T& Add(Args&&... args)
		{
			T& ret = ECS::registry.emplace<std::decay_t<T>>(m_entity, std::forward<Args>(args)...);
			ret.m_parent = m_entity;
			m_children.push_back(ret.m_entity);
			return ret;
		}

		template<class T>
		T& Get()
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_entity);
		}

		template<class T>
		T& GetChild(size_t index)
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_children[index]);
		}

		template<class T>
		T& GetParent()
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_parent);
		}

	public:
		entt::entity m_entity;
		entt::entity m_parent;
		std::vector<entt::entity> m_children;
	};

}