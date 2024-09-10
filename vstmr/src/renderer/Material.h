#pragma once

#include "Shaders.h"
#include "ECS/SceneContainer.h"
#include "Texture.h"

namespace vstmr {

	class Material : public SceneContainer
	{
	public:
		Material();

	public:
		std::vector<Texture> textures;
		glm::vec3 color{ 1.0f, 0.0f, 1.0f };
		Shaders shaders;
	};

}