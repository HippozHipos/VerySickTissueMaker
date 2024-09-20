#pragma once
#include "pch.h"
#include "ECS/ApplicationContainerProvider.h"
#include "SceneContainer.h"

#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Window/MainPlatformWindow.h"
#include "Timer/Timer.h"
#include "Renderer/Renderer.h"

namespace be {

	/*!
	 *  \class ApplicationContainerProvider
	 *  \brief Represents an object in the scene.
	 *
	 *  This class can be inherited from by any class that will be in the scene without any behaviour.
	 *  It inherits from SceneContainer and provides access to the objects stored by ApplicationContainer
	 *  on top of it.
	 *
	 *  Each SceneObject also has a Transform object added to it by default.
	 */
	class ApplicationContainerProvider : public SceneContainer
	{
	public:
		/*!
		* \brief Constructor adds a Transform object
		*/
		ApplicationContainerProvider() = default;

	protected:
		/*!
		 * \brief Gets the "Main Platoform Window"'s Keyboard.
		 * \return Reference to "Main Platoform Window"'s Keyboard stored by ApplicationContainer..
		 */
		Keyboard& GetKeyboard()
		{
			return ECS::registry.get<Keyboard>((entt::entity)0);
		}

		/*!
		 * \brief Gets the "Main Platoform Window"'s Mouse.
		 * \return Reference to "Main Platoform Window"'s Mouse stored by ApplicationContainer..
		 */
		Mouse& GetMouse()
		{
			return ECS::registry.get<Mouse>((entt::entity)0);
		}

		/*!
		 * \brief Gets the "Main Platoform Window" i.e. the Window class.
		 * \return Reference to "Main Platoform Window" i.e. the Window class stored by ApplicationContainer.
		 */
		MainPlatformWindow& GetWindow()
		{
			return ECS::registry.get<MainPlatformWindow>((entt::entity)0);
		}

		/*!
		 * \brief Gets the Timer.
		 * \return Reference to Timer stored by ApplicationContainer.
		 */
		Timer& GetTimer()
		{
			return ECS::registry.get<Timer>((entt::entity)0);
		}

		/*!
		 * \brief Gets the Renderer.
		 * \return Reference to Renderer stored by ApplicationContainer.
		 */
		Renderer& GetRenderer()
		{
			return ECS::registry.get<Renderer>((entt::entity)0);
		}
	};

}