#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"

namespace vstmr {

	void Renderer::Init()
	{
		m_shaders = std::make_shared<Shaders>(
			"../../../../vstmr/assets/shaders/main_vertex_shader.glsl",
			"../../../../vstmr/assets/shaders/main_fragment_shader.glsl");
		m_shaders->Use();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_SCISSOR_TEST);

		CheckOpenGLError();
	}

	void Renderer::Render()
	{
		m_shaders->SetMat4f("projection", camera->GetProjectionMatrix());
		m_shaders->SetMat4f("view", camera->GetViewMatrix());
		camera->UpdateVectors();

		glDrawElements(GL_TRIANGLES, 26700, GL_UNSIGNED_INT, nullptr);
		glClear(GL_DEPTH_BUFFER_BIT);

		CheckOpenGLError();
	}
}