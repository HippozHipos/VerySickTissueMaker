#pragma once
#include "ECS.h"

namespace vstmr {

	class SceneContainer
	{
	public:
		SceneContainer();
		SceneContainer(entt::entity entity);
		virtual ~SceneContainer() = default;

	public:
		template<class T, class... Args>
		T& AddComponent(Args&&... args)
		{
			T& ret = ECS::registry.emplace<std::decay_t<T>>(m_entity, std::forward<Args>(args)...);
			ret._SetEntity(m_entity);
			return ret;
		}

		template<class T>
		T& GetComponent()
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_entity);
		}

		void _SetEntity(entt::entity entity);

	private:
		entt::entity m_entity;
	};

}