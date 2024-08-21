#include "glad/glad.h"

#include "VertexArray.h"
#include "diagnostics/OpenglError.h"

namespace vstm {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_buffer);
		CheckOpenGLError("VertexArray::VertexArray");
	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_buffer);
		CheckOpenGLError("VertexArray::Destroy");
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_buffer);
		CheckOpenGLError("VertexArray::Bind");
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
		CheckOpenGLError("VertexArray::UnBind");
	}

}