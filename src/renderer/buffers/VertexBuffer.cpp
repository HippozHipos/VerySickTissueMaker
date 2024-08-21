#include "glad/glad.h"

#include "VertexBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstm
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_buffer);
		CheckOpenGLError("VertexBuffer::VertexBuffer");
	}

	VertexBuffer::~VertexBuffer()
	{
		//Destroy(); Deallocation of vertex buffers should be handled by renderer. leave it for now for convenience
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		CheckOpenGLError("VertexBuffer::Bind");
	}

	void VertexBuffer::BufferData(size_t size, bool staticDraw)
	{
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		CheckOpenGLError("VertexBuffer::BufferData");
	}

	void VertexBuffer::BufferSubData(void* data, size_t size, size_t offset) 
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		CheckOpenGLError("VertexBuffer::BufferSubData");
	}

	void VertexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer);
		CheckOpenGLError("VertexBuffer::Destroy");
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CheckOpenGLError("VertexBuffer::UnBind");
	}
}