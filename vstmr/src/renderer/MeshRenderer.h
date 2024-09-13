#pragma once

#include "ECS/SceneContainer.h"
#include "MeshComponent.h"
#include "Material.h"

namespace be {

	class MeshRenderer : public SceneContainer
	{
	public:
		MeshRenderer() = default;

	public:
		Material material;
		std::vector<MeshComponent> meshes;
		int draw_mode = GL_FILL;
	};

}