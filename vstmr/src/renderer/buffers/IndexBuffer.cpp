#include "glad/glad.h"

#include "IndexBuffer.h"
#include "diagnostics/OpenglError.h"

namespace vstmr
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_buffer_id);
		CheckOpenGLError();
        
	}

	IndexBuffer::~IndexBuffer()
	{
		//Destroy(); Deallocation of index buffers should be handled by renderer. leave it for now for convenience
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id);
		CheckOpenGLError();
	}

	void IndexBuffer::BufferData(size_t size, bool staticDraw)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		CheckOpenGLError();
	}

	void IndexBuffer::BufferSubData(void* data, size_t size, size_t offset)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		CheckOpenGLError();
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_buffer_id);
		CheckOpenGLError();
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		CheckOpenGLError();
	}
}