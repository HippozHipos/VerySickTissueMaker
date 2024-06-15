#include <iostream>

#include <glad/glad.h>

#include "Window.h"
#include "util/Logger.h"

namespace vstm {

	Window::Window(int width, int height, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share)
	{
		glfwInit();
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//^^feel like this is important, look at what it is later
		m_pwindow = NULL;// glfwCreateWindow(width, height, title, monitor, share);
		
		if (m_pwindow == NULL)
		{
			VSTM_DEBUG_LOGCRITICAL("glfwCreateWindow failed\n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_pwindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VSTM_DEBUG_LOGCRITICAL("Failed to initialize glad\n");
			return;
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::IsClosed()
	{
		return glfwWindowShouldClose(m_pwindow);
	}

}