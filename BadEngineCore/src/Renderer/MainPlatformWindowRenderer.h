#pragma once
#include "pch.h"
#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexArray.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "Shaders.h"
#include "Quad.h"

namespace be {

	class MainPlatformWindowRenderer
	{
	public:
		MainPlatformWindowRenderer(int width, int height);

	public:
		void ResizeContext(int width, int height);
		int GetWidth();
		int GetHeight();
		Quad& GetQuad();
		void BindFrameBuffer();
		void Render();

	private:
		Shaders m_shaders;
		FrameBuffer m_frame_buffer{};
		VertexArray m_vertex_array{};
		VertexBuffer m_vertex_buffer{};
		IndexBuffer m_index_buffer{};
		Quad m_quad;
	};

}