#pragma once
#include "pch.h"
#include "ECS.h"
#include "Diagnostics/Logger.h"

namespace be {

	/*!
	 *  See related: SceneObject
	 *  
	 *  \class SceneContainer
	 *  \brief Represents a container that holds any object that might be in the scene.
	 * 
	 *  Any object that is added to this container becomes one of its children and this container
	 *  becomes that objects parent. NOTE: Any object that can be added to this container should 
	 *	also inherit from SceneContainer. Therefore, you can build hierarchical tree structure of 
	 *  objects with it.
	 *  Example:
	 *  \code
		//narrow gun nozzle
		class NarrowNozzle : public SceneContainer
		{
		public:
			//fire bullet
			void Fire() {  };
		};
	
		//wide gun nozzle
		class WideNozzle : public SceneContainer
		{
		public:
			//fire bullet
			void Fire() {};
		};
	
		//gun with a narrow gun nozzle
		class NarrowNozzleGun : public SceneContainer
		{
		public:
			NarrowNozzleGun()
			{
				Add<NarrowNozzle>(); //add NarrowNozzle object
			}
	
			void Update()
			{
				Get<NarrowNozzle>().Fire(); //fire bullet from narrow nozzle
			}
		};
	
		//gun with a wide gun nozzle
		class WideNozzleGun : public SceneContainer
		{
		public:
			WideNozzleGun()
			{
				Add<WideNozzle>();//add NarrowNozzle object
			}
	
			void Update()
			{
				Get<WideNozzle>().Fire(); //fire bullet from narrow nozzle
			}
		};
	
		//player with 
		class Player : public SceneContainer
		{
		public:
			Player()
			{
				WideNozzleGun& leftHand = Add<WideNozzleGun>();
				NarrowNozzleGun& rightHand = Add<NarrowNozzleGun>();
				//could do more things with leftHand and rightHand here
			}
	
			void Update()
			{
				//player has 2 guns with 2 different behaviour
				Get<WideNozzleGun>().Update(); 
				Get<NarrowNozzleGun>().Update();
			}
		};
	 * 	
	 *	\endcode
	 */
	class SceneContainer
	{
	public:
		/*!
		* \brief Constructor creates an entt::entity, which is the entity that identifies this container.
		*/
		SceneContainer();
		virtual ~SceneContainer() = default;

	public:
		/*!
		 * \brief Adds an object to the container.
		 *
		 * \tparam T Object of type T to be added to this container.
		 * \tparam Args Variadic arguments that will be passed to the constructor of type T when constructing it).
		 * \param args Variadic arguments that will be passed to the constructor of type T when constructing it.
		 * 
		 * \return Object of type T that was just created.
		 */
		template<class T, class... Args>
		T& Add(Args&&... args)
		{
			T& ret = ECS::registry.emplace<std::decay_t<T>>(m_entity, std::forward<Args>(args)...);
			ret.m_parent = m_entity;
			m_children.push_back(ret.m_entity);
			return ret;
		}

		/*!
		 * \brief Gets the object of given type from this container.
		 * \tparam T Object that is to be retrieved.
		 * \return Object of type T that this container stores.
		 */
		template<class T>
		T& Get()
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_entity);
		}

		/*!
		 * \brief Gets the parent container of this container.
		 * \tparam T Type of the parent container.
		 * \return The parent container of this object.
		 */
		template<class T>
		T& GetParent()
		{
			auto view = ECS::registry.view<std::decay_t<T>>();
			return view.get<std::decay_t<T>>(m_parent);
		}

	private:
		entt::entity m_entity;/*!< entt entity that repersents this container. */
		entt::entity m_parent;/*!< parent entt entity of this container. */
		std::vector<entt::entity> m_children;/*!< a vector of all the children containers of this container. */
	};


}