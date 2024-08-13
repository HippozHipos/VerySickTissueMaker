#include "VertexArray.h"

#include "glad/glad.h"

namespace vstm {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_buffer);
	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_buffer);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_buffer);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

}