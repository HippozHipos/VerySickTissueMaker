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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		LoadShaderSource(m_vertex_shader_source_path, m_vertex_shader_source);
		LoadShaderSource(m_fragment_shader_source_path, m_fragment_shader_source);

		m_shaders = std::make_unique<Shaders>(VertexShaderSource(), FragmentShaderSource());
		m_shaders->Use();
		m_vertex_array.Bind();

		m_shaders->SetMat4f("projection", m_camera.GetProjection());
		m_camera.Position.z = -5; m_camera.Rotation.y = 0.5f;
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
		m_shaders->SetMat4f("rotation", m_camera.GetRotation());
		m_shaders->SetMat4f("translation", m_camera.GetTranslation());
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetLayout()
	{
		m_vertex_array.SetupLayout<float>(3);
		m_vertex_array.AddLayout();
	}
}