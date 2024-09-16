#include <glad/glad.h>

#include "VertexArray.h"
#include "Diagnostics/OpenglError.h"

namespace be {

	void VertexArray::Init()
	{
		glGenVertexArrays(1, &m_buffer_id);
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_buffer_id);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_buffer_id);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

}