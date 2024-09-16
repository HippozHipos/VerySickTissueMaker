#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Diagnostics/OpenglError.h"

namespace be
{
	void IndexBuffer::Init()
	{
		glGenBuffers(1, &m_buffer_id);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
	}

	void IndexBuffer::BufferData(void* data, size_t size, bool staticDraw)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void IndexBuffer::BufferSubData(void* data, size_t size, size_t offset)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer_id);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}