#include <glad/glad.h>

#include "VertexArray.h"
#include "diagnostics/OpenglError.h"

namespace be {

	void VertexArray::Init()
	{
		glGenVertexArrays(1, &m_buffer_id);
		CheckOpenGLError();
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_buffer_id);
		CheckOpenGLError();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_buffer_id);
		CheckOpenGLError();
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
		CheckOpenGLError();
	}

}