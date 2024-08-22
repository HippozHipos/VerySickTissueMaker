#pragma once

#include <string>
#include <memory>

#include "Shaders.h"
#include "buffers/VertexArray.h"

#include "camera/Camera.h"

namespace vstm {

	class Renderer
	{
	public:
		Renderer();
		~Renderer() = default;

	public:
		const std::string& VertexShaderSource();
		const std::string& FragmentShaderSource();
		void Render();
		PerspectiveCamera& GetCamera();

		//NOTE: This function is only here to make it work for now. It setsup layout of vertex buffer.
		void SetLayout();

	private:
		void LoadShaderSource(const char* path, std::string& source);

	private:
		PerspectiveCamera m_camera{ glm::radians(90.0f), 600.0f / 600.0f, 0.1f, 100.0f };

		const char* m_vertex_shader_source_path = "../../../assets/shaders/vertex_shader.shader";
		const char* m_fragment_shader_source_path = "../../../assets/shaders/fragment_shader.shader";

		std::string m_vertex_shader_source;
		std::string m_fragment_shader_source;

		std::unique_ptr<Shaders> m_shaders;
		VertexArray m_vertex_array{};

	};

}