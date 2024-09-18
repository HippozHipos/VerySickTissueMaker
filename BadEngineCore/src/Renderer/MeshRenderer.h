#pragma once
#include "pch.h"
#include "ECS/SceneContainer.h"
#include "Mesh.h"
#include "Material.h"

namespace be {

	class MeshRenderer : public SceneContainer
	{
	public:
		MeshRenderer() = default;

	public:
		Material material;
		std::vector<Mesh> meshes;
		int draw_mode = GL_FILL;
	};

}