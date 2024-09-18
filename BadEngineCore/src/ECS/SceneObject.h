#pragma once
#include "pch.h"
#include "ECS/SceneContainer.h"
#include "Renderer/Transform.h"

#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Window/Window.h"
#include "Timer/Timer.h"
#include "Renderer/Renderer.h"

namespace be {

	/*!
	 *  \class SceneObject
	 *  \brief Represents an object in the scene. 
	 *
	 *  This class can be inherited from by any class that will be in the scene without any behaviour.
	 *  It inherits from SceneContainer and provides access to the objects stored by ApplicationContainer
	 *  on top of it.
	 * 
	 *  Each SceneObject also has a Transform object added to it by default.
	 */
	class SceneObject : public SceneContainer
	{
	public:
		/*!
		* \brief Constructor adds a Transform object
		*/
		SceneObject();

	protected:
		/*!
		 * \brief Gets the "Main Platoform Window"'s Keyboard.
		 * \return Reference to "Main Platoform Window"'s Keyboard stored by ApplicationContainer..
		 */
		Keyboard& GetKeyboard()
		{
			auto view = ECS::registry.view<Keyboard>();
			return view.get<Keyboard>(entt::entity(0));
		}

		/*!
		 * \brief Gets the "Main Platoform Window"'s Mouse.
		 * \return Reference to "Main Platoform Window"'s Mouse stored by ApplicationContainer..
		 */
		Mouse& GetMouse()
		{
			auto view = ECS::registry.view<Mouse>();
			return view.get<Mouse>(entt::entity(0));
		}

		/*!
		 * \brief Gets the "Main Platoform Window" i.e. the Window class.
		 * \return Reference to "Main Platoform Window" i.e. the Window class stored by ApplicationContainer.
		 */
		Window& GetWindow()
		{
			auto view = ECS::registry.view<Window>();
			return view.get<Window>(entt::entity(0));
		}

		/*!
		 * \brief Gets the Timer.
		 * \return Reference to Timer stored by ApplicationContainer.
		 */
		Timer& GetTimer()
		{
			auto view = ECS::registry.view<Timer>();
			return view.get<Timer>(entt::entity(0));
		}

		/*!
		 * \brief Gets the Renderer.
		 * \return Reference to Renderer stored by ApplicationContainer.
		 */
		Renderer& GetRenderer()
		{
			auto view = ECS::registry.view<Renderer>();
			return view.get<Renderer>(entt::entity(0));
		}
	};

}