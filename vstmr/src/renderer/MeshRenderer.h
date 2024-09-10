#pragma once

#include "ECS/SceneContainer.h"
#include "MeshComponent.h"
#include "Material.h"

namespace vstmr {

	class MeshRenderer : public SceneContainer
	{
	public:
		MeshRenderer() = default;

	public:
		Material material;
		std::vector<MeshComponent> meshes;
		bool wireframe_mode = false;
	};

}