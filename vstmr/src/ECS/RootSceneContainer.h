#pragma once

#include <entt/entt.hpp>
#include "SceneContainer.h"
#include "ECS.h"

namespace vstmr {

	//The first scene container that contains every other scene container
	class RootSceneContainer : public SceneContainer
	{
	public:
		RootSceneContainer();

	public:
		[[NODISCARD]] SceneContainer& CreateSceneContainer();

	};

}