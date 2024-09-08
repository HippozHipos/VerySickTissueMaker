#pragma once

#include <vector>
#include <functional>

#include "ECS/ECS.h"

//REMINDER: We currenly simply store the function pointers. What happens if the object that the pointer
//belongs to goes out of scope? GG. So need to add a mechanism to remove pointers when object goes out
//of scope. Probably need to change from vector to something else. And add something in BehaviouralSceneObject's
//destructor that lets BehaviourManager know that it has been destroyed so that it will remove its assosiated
//functions

namespace vstmr {

	//defaults
	template <class T, class = void>
	struct HasStartMethod : std::false_type {};
	template <class T, class = void>
	struct HasUpdateMethod : std::false_type {};
	template <class T, class = void>
	struct HasUIMethod : std::false_type {};
	template <class T, class = void>
	struct HasEndMethod : std::false_type {};

	//has methods
	template <class T>
	struct HasStartMethod<T, std::void_t<decltype(std::declval<T>().Start())>> : std::true_type {};
	template <class T>
	struct HasUpdateMethod<T, std::void_t<decltype(std::declval<T>().Update())>> : std::true_type {};
	template <class T>
	struct HasUIMethod<T, std::void_t<decltype(std::declval<T>().UI())>> : std::true_type {};
	template <class T>
	struct HasEndMethod<T, std::void_t<decltype(std::declval<T>().End())>> : std::true_type {};

	class BehaviourManager
	{
	public:
		BehaviourManager() = default;

	public:
		template<template<class> class BehaviouralSceneObject, class T>
		void AddBehaviour(BehaviouralSceneObject<T>& thing)
		{
			if constexpr (HasStartMethod<T>::value)
			{
				m_start_functions.push_back([&thing] { static_cast<T*>(&thing)->Start(); });
			}
			if constexpr (HasUpdateMethod<T>::value)
			{
				m_update_functions.push_back([&thing] { static_cast<T*>(&thing)->Update(); });
			}
			if constexpr (HasUIMethod<T>::value)
			{
				m_gui_functions.push_back([&thing] { static_cast<T*>(&thing)->UI(); });
			}
			if constexpr (HasEndMethod<T>::value)
			{
				m_end_functions.push_back([&thing] { static_cast<T*>(&thing)->End(); });
			}
		}

		void CallAllStartFunctions() const;
		void CallAllUpdateFunctions() const;
		void CallAllUIFunctions() const;
		void CallAllEndFunctions() const;

	private:
		std::vector<std::function<void()>> m_start_functions;
		std::vector<std::function<void()>> m_update_functions;
		std::vector<std::function<void()>> m_gui_functions;
		std::vector<std::function<void()>> m_end_functions;
	};

}