#include "Quad.h"

namespace vstmr {

	Quad::Quad(float width, float height, float centerx, float centery)
	{
		SetRect(width, height, centerx, centery);
	}

	void Quad::SetRect(float x, float y, float width, float height)
	{
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;
		
		m_vertices[0] = x - halfWidth; m_vertices[1] = y + halfHeight;
		m_vertices[2] = 0.0f; m_vertices[3] = 1.0f;
		m_vertices[4] = x - halfWidth; m_vertices[5] = y - halfHeight;
		m_vertices[6] = 0.0f; m_vertices[7] = 0.0f;
		m_vertices[8] = x + halfWidth; m_vertices[9] = y - halfHeight;
		m_vertices[10] = 1.0f; m_vertices[11] = 0.0f;
		m_vertices[12] = x + halfWidth; m_vertices[12] = y + halfHeight;
		m_vertices[14] = 1.0f; m_vertices[15] = 1.0f;
	}

	float* Quad::GetVertexData()
	{
		return m_vertices;
	}

	unsigned int* Quad::GetIndexData()
	{
		return m_indices;
	}

	int Quad::GetVertexBufferSize()
	{
		return sizeof(m_vertices);
	}

	int Quad::GetIndexBufferSize()
	{
		return sizeof(m_indices);
	}

	int Quad::GetIndexBufferCount()
	{
		return m_index_buffer_size;
	}

}