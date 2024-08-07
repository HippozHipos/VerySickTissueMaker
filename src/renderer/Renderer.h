#pragma once

#include <string>
#include <memory>

#include "Shaders.h"

namespace vstm {

	
	//NOTE: Should eventually make vertex and fragment shader classes but its fine for now.
	class Renderer
	{
	public:
		Renderer();
		~Renderer() = default;

	public:
		const std::string& VertexShaderSource();
		const std::string& FragmentShaderSource();

	private:
		void LoadShaderSource(const char* path, std::string& source);

	private:
		const char* m_vertex_shader_source_path = "../../../assets/shaders/vertex_shader.shader";
		const char* m_fragment_shader_source_path = "../../../assets/shaders/fragment_shader.shader";

		std::string m_vertex_shader_source;
		std::string m_fragment_shader_source;

		std::unique_ptr<Shaders> m_shaders;
	};

}