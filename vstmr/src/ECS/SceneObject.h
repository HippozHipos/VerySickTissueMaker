#pragma once

#include "ECS/SceneContainer.h"
#include "renderer/Transform.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "window/Window.h"
#include "timer/Timer.h"
#include "renderer/Renderer.h"

namespace be {

	class SceneObject : public SceneContainer
	{
	public:
		SceneObject();

	protected:
		//These functions work because:
		//ApplicationContainer in Application.h is _ALWAYS_ the first entity that is created
		//and these objects are stores in ApplicationContainer
		Keyboard& GetKeyboard()
		{
			auto view = ECS::registry.view<Keyboard>();
			return view.get<Keyboard>(entt::entity(0));
		}

		Mouse& GetMouse()
		{
			auto view = ECS::registry.view<Mouse>();
			return view.get<Mouse>(entt::entity(0));
		}

		Window& GetWindow()
		{
			auto view = ECS::registry.view<Window>();
			return view.get<Window>(entt::entity(0));
		}

		Timer& GetTimer()
		{
			auto view = ECS::registry.view<Timer>();
			return view.get<Timer>(entt::entity(0));
		}

		Renderer& GetRenderer()
		{
			auto view = ECS::registry.view<Renderer>();
			return view.get<Renderer>(entt::entity(0));
		}
	};

}