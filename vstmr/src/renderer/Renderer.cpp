#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "diagnostics/Logger.h"
#include "diagnostics/OpenglError.h"
#include "window/Window.h"

namespace vstmr {


	Renderer::Renderer(Window* window) :
		m_window{ window }
	{
		m_shaders = std::make_unique<Shaders>();
		m_shaders->Use();
		m_vertex_array.Bind();

		m_shaders->SetMat4f("projection", m_camera.GetProjectionMatrix());
		//m_shaders->SetInt("tex0", 0);
	
		// Enable depth testing and backface culling
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		CheckOpenGLError();
	}

	PerspectiveCamera& Renderer::GetActiveCamera() 
	{ 
		return m_camera; 
	}

	void Renderer::Render()
	{
		m_vertex_array.Bind();
		m_shaders->SetMat4f("view", m_camera.GetViewMatrix());
		m_camera.UpdateVectors();

		// Clear both color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 26700, GL_UNSIGNED_INT, nullptr);

		CheckOpenGLError();
	}

	void Renderer::SetLayout()
	{
		m_vertex_array.SetupLayout<float>(3);  // Position (x, y, z)
		//m_vertex_array.SetupLayout<float>(4);  // Color (r, g, b, a)
		//m_vertex_array.SetupLayout<float>(2);  // Texture coordinates (u, v)

		m_vertex_array.AddLayout();

		CheckOpenGLError();
	}
}