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
		//TODO: Take framebuffer from window as argument
		Renderer();
		~Renderer() = default;

	public:
		void Render();
		PerspectiveCamera& GetActiveCamera();

		//NOTE: This function is only here to make it work for now. It setsup layout of vertex buffer.
		void SetLayout();

	private:
		PerspectiveCamera m_camera{ glm::radians(90.0f), 600.0f / 600.0f, 0.1f, 100.0f };

		std::unique_ptr<Shaders> m_shaders;
		VertexArray m_vertex_array{};

	};

}