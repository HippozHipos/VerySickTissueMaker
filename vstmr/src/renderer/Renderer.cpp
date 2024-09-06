#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"

namespace vstmr {

	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		CheckOpenGLError();
	}

	void Renderer::Render()
	{
		m_mesh_renderer.Light();
		m_mesh_renderer.Render();
	}
}