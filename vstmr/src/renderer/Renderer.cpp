#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"

#include "Graphics.h"

namespace be {

	Renderer::Renderer(int width, int height) :
		m_main_window_renderer{ width, height },
		m_mesh_renderer{ m_viewport_map, m_main_window_renderer }
	{
	}

	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		CheckOpenGLError();
	}

	void Renderer::CreateViewport(const char* name)
	{
		m_viewport_map.insert(std::pair<const char*, VstmrImGuiViewport>(name, VstmrImGuiViewport{ name }));
	}

	void Renderer::RenderImGuiViewport()
	{
		for (auto& [_, viewport] : m_viewport_map) 
		{
			viewport.Render();
		}
	}

	void Renderer::Render()
	{
		m_mesh_renderer.Render();
	}
}