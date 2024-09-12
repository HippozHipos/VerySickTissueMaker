#pragma once

#include <string>
#include <memory>

#include "Shaders.h"

#include "ECS/SceneContainer.h"
#include "UI/imgui/VstmrImGuiViewport.h"
#include "ECSSystems/MeshRendererSystem.h"

namespace vstmr {

	class Window;
	class Renderer : public SceneContainer
	{
	public:
		Renderer() = default;
		
	public:
		void Init();
		void Render();
		void RenderImGuiViewport();
		void CreateViewport(const char* name);

	private:
		std::unordered_map<std::string, VstmrImGuiViewport> m_viewport_map;
		MeshRendererSystem m_mesh_renderer{ m_viewport_map };
	};

}