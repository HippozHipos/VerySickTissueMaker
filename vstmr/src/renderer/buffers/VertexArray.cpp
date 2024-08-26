#include "glad/glad.h"

#include "VertexArray.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_buffer);
		CheckOpenGLError();
	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_buffer);
		CheckOpenGLError();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_buffer);
		CheckOpenGLError();
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
		CheckOpenGLError();
	}

}