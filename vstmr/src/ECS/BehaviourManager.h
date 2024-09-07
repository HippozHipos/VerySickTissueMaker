#pragma once

#include <vector>
#include <functional>

#include "ECS/ECS.h"

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
	struct HasStartMethod<T, std::void_t<decltype(std::declval<T>().StartCaller())>> : std::true_type {};
	template <class T>
	struct HasUpdateMethod<T, std::void_t<decltype(std::declval<T>().UpdateCaller())>> : std::true_type {};
	template <class T>
	struct HasUIMethod<T, std::void_t<decltype(std::declval<T>().UICaller())>> : std::true_type {};
	template <class T>
	struct HasEndMethod<T, std::void_t<decltype(std::declval<T>().EndCaller())>> : std::true_type {};

	class BehaviourManager
	{
	public:
		BehaviourManager() = default;

	public:
		template<class T>
		void AddBehaviour(T& thing)
		{
			/*if constexpr (HasStartMethod<T>::value)
			{
				m_start_functions.push_back([&thing] { thing.StartCaller(); });
			}
			if constexpr (HasUpdateMethod<T>::value)
			{
				m_update_functions.push_back([&thing] { thing.UpdateCaller(); });
			}
			if constexpr (HasUIMethod<T>::value)
			{
				m_gui_functions.push_back([&thing] { thing.UICaller(); });
			}
			if constexpr (HasEndMethod<T>::value)
			{
				m_end_functions.push_back([&thing] { thing.EndCaller(); });
			}*/

			m_start_functions.push_back([&thing] { thing.StartCaller(); });
			m_update_functions.push_back([&thing] { thing.UpdateCaller(); });
			m_gui_functions.push_back([&thing] { thing.UICaller(); });
			m_end_functions.push_back([&thing] { thing.EndCaller(); });
		}

		void CallAllStart() const;

	private:
		std::vector<std::function<void()>> m_start_functions;
		std::vector<std::function<void()>> m_update_functions;
		std::vector<std::function<void()>> m_gui_functions;
		std::vector<std::function<void()>> m_end_functions;
	};

}