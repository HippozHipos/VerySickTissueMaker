#pragma once

#include "Vector.h"
#include "ECS/SceneContainer.h"

namespace vstmr {

	struct Transform : public SceneContainer
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	};

}

