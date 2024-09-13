#pragma once

#include "pch.h"
#include <functional>

#include "ECS/ECS.h"

//REMINDER: We currenly simply store the function pointers. What happens if the object that the pointer
//belongs to goes out of scope? GG. So need to add a mechanism to remove pointers when object goes out
//of scope. Probably need to change from vector to something else. And add something in BehaviouralSceneObject's
//destructor that lets BehaviourManager know that it has been destroyed so that it will remove its assosiated
//functions

namespace be {

	//defaults
	template <class T, class = void>
	struct HasPreStartMethod : std::false_type {};
	template <class T, class = void>
	struct HasStartMethod : std::false_type {};
	template <class T, class = void>
	struct HasUpdateMethod : std::false_type {};
	template <class T, class = void>
	struct HasUIMethod : std::false_type {};
	template <class T, class = void>
	struct HasEndMethod : std::false_type {};
	template <class T, class = void>
	struct HasPostEndMethod : std::false_type {};


	//has methods
	template <class T>
	struct HasPreStartMethod<T, std::void_t<decltype(std::declval<T>().PreStart())>> : std::true_type {};
	template <class T>
	struct HasStartMethod<T, std::void_t<decltype(std::declval<T>().Start())>> : std::true_type {};
	template <class T>
	struct HasUpdateMethod<T, std::void_t<decltype(std::declval<T>().Update())>> : std::true_type {};
	template <class T>
	struct HasUIMethod<T, std::void_t<decltype(std::declval<T>().UI())>> : std::true_type {};
	template <class T>
	struct HasEndMethod<T, std::void_t<decltype(std::declval<T>().End())>> : std::true_type {};
	template <class T>
	struct HasPostEndMethod<T, std::void_t<decltype(std::declval<T>().PostEnd())>> : std::true_type {};

	class BehaviourManager
	{
	public:
		BehaviourManager() = default;

	public:
		template<template<class> class BehaviouralSceneObject, class T>
		void AddBehaviour(BehaviouralSceneObject<T>* thing)
		{
			//call prestart
			if constexpr (HasPreStartMethod<T>::value)
			{
				static_cast<T*>(thing)->PreStart();
			}
			if constexpr (HasStartMethod<T>::value)
			{
				m_start_functions.push_back(std::pair<void*, std::function<void()>>(static_cast<void*>(thing), [thing] { static_cast<T*>(thing)->Start(); }));
			}
			if constexpr (HasUpdateMethod<T>::value)
			{
				m_update_functions.push_back(std::pair<void*, std::function<void()>>(static_cast<void*>(thing), [thing] { static_cast<T*>(thing)->Update(); }));
			}
			if constexpr (HasUIMethod<T>::value)
			{
				m_gui_functions.push_back(std::pair<void*, std::function<void()>>(static_cast<void*>(thing), [thing] { static_cast<T*>(thing)->UI(); }));
			}
		}

		void CallAllStartFunctions() const;
		void CallAllUpdateFunctions() const;
		void CallAllUIFunctions() const;
		void CallAllEndFunctions() const;

		template<template<class> class BehaviouralSceneObject, class T>
		void RemoveBehaviour(BehaviouralSceneObject<T>* thing)
		{
			if constexpr (HasEndMethod<T>::value)
			{
				static_cast<T*>(thing)->End();
			}

			if constexpr (HasPostEndMethod<T>::value)
			{
				static_cast<T*>(thing)->PostEnd();
			}

			RemoveBehaviourFromList(m_start_functions, thing);
			RemoveBehaviourFromList(m_update_functions, thing);
			RemoveBehaviourFromList(m_gui_functions, thing);
		}

	private:
		template<class T>
		void RemoveBehaviourFromList(std::list<std::pair<void*, std::function<void()>>>& list, T* thing)
		{
			for (auto it = list.begin(); it != list.end(); it++)
			{
				if (static_cast<T*>(it->first) == thing)
				{
					it = list.erase(it);
					return;
				}
			}
		}

	private:
		std::list<std::pair<void*, std::function<void()>>> m_start_functions;
		std::list<std::pair<void*, std::function<void()>>> m_update_functions;
		std::list<std::pair<void*, std::function<void()>>> m_gui_functions;
	};

}