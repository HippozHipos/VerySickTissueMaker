#pragma once

#include "ECS/SceneContainer.h"
#include "renderer/Transform.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"

namespace vstmr {

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
	};

}