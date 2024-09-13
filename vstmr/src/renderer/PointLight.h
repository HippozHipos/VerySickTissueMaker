#pragma once
#include "pch.h"
#include <glm/glm.hpp>

#include "ECS/SceneContainer.h"

namespace be {

	class PointLight : public SceneContainer
	{
	public:
		PointLight() = default;

	public:
		glm::vec3 color{};
	};

}