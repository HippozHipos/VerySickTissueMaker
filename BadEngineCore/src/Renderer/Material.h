#pragma once
#include "pch.h"
#include "Shaders.h"
#include "ECS/SceneContainer.h"
#include "Texture.h"

namespace be {

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