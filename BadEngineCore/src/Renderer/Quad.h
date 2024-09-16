#pragma once
#include "pch.h"
#include "Texture.h"

namespace be {

	class Quad
	{
	public:
		Quad() = default;
		Quad(float width, float height, float centerx, float centery);

	public:
		void SetRect(float x, float y, float width, float height);
		int GetVertexBufferSize();
		int GetIndexBufferSize();
		int GetIndexBufferCount();
		float* GetVertexData();
		unsigned int* GetIndexData();

	private:
		static constexpr int m_vertex_buffer_size = 16;
		static constexpr int m_index_buffer_size = 6;

		float m_vertices[m_vertex_buffer_size] =
		{
			//position      //textures
			-1.0f,  1.0f,   0.0f, 1.0f,
			-1.0f, -1.0f,   0.0f, 0.0f,
			 1.0f, -1.0f,   1.0f, 0.0f,                       
			 1.0f,  1.0f,   1.0f, 1.0f
		};

		unsigned int m_indices[m_index_buffer_size] =
		{
			0, 1, 2,   
			0, 2, 3    
		};

	};

}