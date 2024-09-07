#pragma once

#include "ECS/ECS.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"

namespace vstmr {

	struct PerspectiveCamera;
	struct Transform;
	struct Material;

	struct MeshRendererProcessor
	{
		void Render();
	private:
		void ProcessLighting(MeshRenderer& renderer, Material& material);
		void RenderMesh(PerspectiveCamera& camera, MeshRenderer& renderer, Transform& transform, VectorComponent<MeshComponent>& meshes, Material& material);
	};

}