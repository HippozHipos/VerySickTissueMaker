#pragma once
#include "pch.h"
#include <glm/glm.hpp>

#include "ECS/SceneObject.h"

namespace be {

	class PointLight : public SceneContainer
	{
	public:
		PointLight(const char* path = nullptr);

	public:
		glm::vec3 color{};
	};

}