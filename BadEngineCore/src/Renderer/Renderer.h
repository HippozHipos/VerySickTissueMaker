#pragma once

#include "pch.h"

#include "Shaders.h"

#include "ECS/SceneContainer.h"
#include "UI/Imgui/BEImGuiViewport.h"
#include "ECSSystems/MeshRendererSystem.h"
#include "MainPlatformWindowRenderer.h"

namespace be {

	class MainPlatformWindow;
	class Renderer : public SceneContainer
	{
	public:
		Renderer(int width, int height);
		
	public:
		void Init();
		void Render();
		void RenderImGuiViewport();
		std::unordered_map<std::string, BEImGuiViewport>::iterator CreateViewport(const char* name);
		std::unordered_map<std::string, BEImGuiViewport>::iterator GetViewport(const char* name);

	private:
		std::unordered_map<std::string, BEImGuiViewport> m_viewport_map;
		MeshRendererSystem m_mesh_renderer;
		MainPlatformWindowRenderer m_main_window_renderer;
	};

}