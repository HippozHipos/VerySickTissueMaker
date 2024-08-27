#include <glad/glad.h>

#include "Viewport.h"

namespace vstmr {

	Viewport::Viewport(int x, int y, int width, int height) :
		m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height }
	{
	}

	void Viewport::UpdateViewport()
	{
		glViewport(m_x, m_y, m_width, m_height);
		glScissor(m_x, m_y, m_width, m_height);
	}

}
