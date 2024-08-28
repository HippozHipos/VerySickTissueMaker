#include <glad/glad.h>

#include "Viewport.h"
#include "window/Window.h"
#include "diagnostics/Logger.h"

namespace vstmr {

	Viewport::Viewport(int x, int y, int width, int height, Window* window) :
		x{ x }, y{ y }, width{ width }, height{ height }, m_window{ window }
	{
	}

	PerspectiveCamera& Viewport::GetCamera()
	{
		
		return m_camera;
	}

	FrameBuffer& Viewport::GetFrameBuffer()
	{
		return m_FrameBuffer;
	}

	void Viewport::UpdateViewport()
	{
		glViewport(x, m_window->GetHeight() - y - height , width, height);
		glScissor(x, m_window->GetHeight() - y - height, width, height);
	}

	void Viewport::ClearColor(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
