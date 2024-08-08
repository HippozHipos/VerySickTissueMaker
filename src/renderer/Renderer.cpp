#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "util/Logger.h"

namespace vstm {


	Renderer::Renderer()
	{
		LoadShaderSource(m_vertex_shader_source_path, m_vertex_shader_source);
		LoadShaderSource(m_fragment_shader_source_path, m_fragment_shader_source);
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

}