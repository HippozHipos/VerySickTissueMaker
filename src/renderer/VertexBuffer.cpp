#include "VertexBuffer.h"
#include "glad/glad.h"

namespace vstm
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		//Destroy(); Deallocation of vertex buffers should be handled by renderer. leave it for now for convenience
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	}

	void VertexBuffer::BufferData(size_t size, bool staticDraw)
	{
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::BufferSubData(void* data, size_t size, size_t offset) 
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void VertexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}