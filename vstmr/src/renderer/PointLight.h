#pragma once
#include <glm/glm.hpp>

#include "ECS/SceneContainer.h"

namespace vstmr {

	class PointLight : public SceneContainer
	{
	public:
		PointLight() = default;

	public:
		glm::vec3 color{};
	};

}