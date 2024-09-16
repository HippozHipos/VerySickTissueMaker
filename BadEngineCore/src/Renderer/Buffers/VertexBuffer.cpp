#include "glad/glad.h"

#include "VertexBuffer.h"
#include "diagnostics/OpenglError.h"

namespace be
{
	void VertexBuffer::Init()
	{
		glGenBuffers(1, &m_buffer_id);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id);
	}

	void VertexBuffer::BufferData(void* data, size_t size, bool staticDraw)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::BufferSubData(void* data, size_t size, size_t offset) 
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void VertexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer_id);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}