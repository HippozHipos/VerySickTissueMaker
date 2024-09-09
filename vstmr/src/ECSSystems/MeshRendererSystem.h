#pragma once

#include "ECS/ECS.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"

namespace vstmr {

	struct Camera;
	struct Transform;
	struct Material;

	struct MeshRendererSystem
	{
		void Render();
	private:
		void ProcessLighting(MeshRenderer& renderer, Material& material);
		void RenderMesh(Camera& camera, MeshRenderer& renderer, Transform& transform, VectorComponent<MeshComponent>& meshes, Material& material);
	};

}