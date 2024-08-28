#include <glad/glad.h>

#include "Viewport.h"
#include "window/Window.h"
#include "diagnostics/Logger.h"

namespace vstmr {

	Viewport::Viewport(int x, int y, int width, int height, Window* window) :
		m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height }, m_window{ window }
	{
	}



	PerspectiveCamera& Viewport::GetCamera()
	{
		return m_camera;
	}

	void Viewport::UpdateViewport()
	{
		glViewport(m_x, m_window->GetHeight() - m_y - m_height , m_width, m_height);
		glScissor(m_x, m_window->GetHeight() - m_y - m_height, m_width, m_height);
	}

}
