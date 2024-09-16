#pragma once

#include "pch.h"

#include "Shaders.h"

#include "ECS/SceneContainer.h"
#include "UI/Imgui/VstmrImGuiViewport.h"
#include "ECSSystems/MeshRendererSystem.h"
#include "MainPlatformWindowRenderer.h"

namespace be {

	class Window;
	class Renderer : public SceneContainer
	{
	public:
		Renderer(int width, int height);
		
	public:
		void Init();
		void Render();
		void RenderImGuiViewport();
		void CreateViewport(const char* name);

	private:
		std::unordered_map<std::string, VstmrImGuiViewport> m_viewport_map;
		MeshRendererSystem m_mesh_renderer;
		MainPlatformWindowRenderer m_main_window_renderer;
	};

}