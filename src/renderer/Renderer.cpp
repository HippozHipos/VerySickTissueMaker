#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "util/Logger.h"

namespace vstm {


	Renderer::Renderer()
	{
		//REMINDER: THIS LINE FOR WIREFRAME
		LoadShaderSource(m_vertex_shader_source_path, m_vertex_shader_source);
		LoadShaderSource(m_fragment_shader_source_path, m_fragment_shader_source);

		m_shaders = std::make_unique<Shaders>(VertexShaderSource(), FragmentShaderSource());
		m_shaders->Use();
		m_vertex_array.Bind();

		m_shaders->SetMat4f("projection", m_camera.GetProjectionMatrix());
		m_shaders->SetInt("tex0", 0);
	
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);
	}

	PerspectiveCamera& Renderer::GetCamera() 
	{ 
		return m_camera; 
	}

	const std::string& Renderer::VertexShaderSource()
	{
		return m_vertex_shader_source;
	}

	const std::string& Renderer::FragmentShaderSource()
	{
		return m_fragment_shader_source;
	}

	void Renderer::LoadShaderSource(const char* path, std::string& source)
	{
		std::ifstream inStream{ path };
		if (errno != 0)
		{
			VSTM_DEBUG_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", errno, strerror(errno));
			VSTM_CON_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", errno, strerror(errno));
		}
		std::ostringstream oss;
		oss << inStream.rdbuf();
		source = oss.str();
	}

	void Renderer::Render()
	{
		m_vertex_array.Bind();
		m_shaders->SetMat4f("view", m_camera.GetViewMatrix());
		m_camera.UpdateVectors();

		// Clear both color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetLayout()
	{
		m_vertex_array.SetupLayout<float>(3);  // Position (x, y, z)
		m_vertex_array.SetupLayout<float>(4);  // Color (r, g, b, a)
		m_vertex_array.SetupLayout<float>(2);  // Texture coordinates (u, v)

		m_vertex_array.AddLayout();
	}
}