#pragma once

#include "Shaders.h"
#include "ECS/Component.h"

namespace vstmr {

	class Material : public Component
	{
	public:
		Material();

	public:
		glm::vec3 color{ 1.0f, 0.0f, 1.0f };
		Shaders shaders;
	};

}