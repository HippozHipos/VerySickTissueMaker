#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"
#include "Viewport.h"

namespace vstmr {

	Renderer::Renderer(Window* window) :
		m_window{ window }
	{
		m_shaders = std::make_unique<Shaders>(
			"../../../../vstmr/assets/shaders/main_vertex_shader.glsl",
			"../../../../vstmr/assets/shaders/main_fragment_shader.glsl");
		m_shaders->Use();

		// Enable depth testing and backface culling
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_SCISSOR_TEST);

		//m_vertex_array.Bind();

		CheckOpenGLError();
	}

	void Renderer::Render()
	{
		Viewport& viewport = m_window->GetViewport();

		vstmr::PerspectiveCamera& camera = viewport.GetCamera();
		m_shaders->SetMat4f("projection", camera.GetProjectionMatrix());
		m_shaders->SetMat4f("view", camera.GetViewMatrix());
		camera.UpdateVectors();

		viewport.UpdateViewport();

		glDrawElements(GL_TRIANGLES, 26700, GL_UNSIGNED_INT, nullptr);
		glClear(GL_DEPTH_BUFFER_BIT);

		CheckOpenGLError();
	}

	/*void Renderer::SetLayout()
	{
		vArray.Bind();
		vArray.SetupLayout<float>(3);
		vArray.AddLayout();

		CheckOpenGLError();
	}*/
}