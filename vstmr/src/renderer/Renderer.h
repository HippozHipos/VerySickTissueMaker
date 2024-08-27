#pragma once

#include <string>
#include <memory>

#include "Shaders.h"
#include "buffers/VertexArray.h"

#include "camera/Camera.h"

namespace vstmr {

	class Window;
	class Renderer
	{
	public:
		//TODO: Take framebuffer from window as argument
		Renderer(Window* window);
		~Renderer() = default;

	public:
		void Render();

		//NOTE: This function is only here to make it work for now. It setsup layout of vertex buffer.
		void SetLayout();

	private:
		std::unique_ptr<Shaders> m_shaders;
		VertexArray m_vertex_array{};
		Window* m_window;
	};

}