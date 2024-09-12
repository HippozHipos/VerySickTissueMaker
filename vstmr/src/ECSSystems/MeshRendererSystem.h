#pragma once

#include "ECS/ECS.h"
#include "renderer/MeshComponent.h"
#include "renderer/MeshRenderer.h"
#include "renderer/buffers/FrameBuffer.h"

#include "UI/imgui/VstmrImGuiViewport.h"

namespace vstmr {

	struct Camera;
	struct Transform;
	struct Material;

	struct MeshRendererSystem
	{
	public:
		MeshRendererSystem(std::unordered_map<std::string, VstmrImGuiViewport>& viewportMap);

	public:
		void Render();

	private:
		void ProcessLighting(MeshRenderer& renderer);
		void RenderMesh(Camera& camera, MeshRenderer& renderer, Transform& transform);
	
	private:
		std::unordered_map<std::string, VstmrImGuiViewport>& m_viewport_map;
	};

}