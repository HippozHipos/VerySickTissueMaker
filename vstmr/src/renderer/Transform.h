#pragma once

#include "Vector.h"
#include "ECS/Component.h"

namespace vstmr {

	struct Transform : public Component
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	};

}

