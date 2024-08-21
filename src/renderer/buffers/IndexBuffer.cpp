#include "glad/glad.h"

#include "IndexBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstm
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_buffer);
		CheckOpenGLError("IndexBuffer::IndexBuffer");
	}

	IndexBuffer::~IndexBuffer()
	{
		//Destroy(); Deallocation of index buffers should be handled by renderer. leave it for now for convenience
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
		CheckOpenGLError("IndexBuffer::Bind");
	}

	void IndexBuffer::BufferData(size_t size, bool staticDraw)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		CheckOpenGLError("IndexBuffer::BufferData");
	}

	void IndexBuffer::BufferSubData(void* data, size_t size, size_t offset)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		CheckOpenGLError("IndexBuffer::BufferSubData");
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer);
		CheckOpenGLError("IndexBuffer::Destroy");
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		CheckOpenGLError("IndexBuffer::UnBind");
	}
}