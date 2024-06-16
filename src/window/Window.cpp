#include <glad/glad.h>

#include "Window.h"
#include "util/Logger.h"


namespace vstm {

	void keyCallback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window && action == GLFW_PRESS)
		{
			window->OnKeyPressed(key);
			window->OnKeyHeld(key);
		}
		if (window && action == GLFW_RELEASE)
		{
			window->OnKeyRelease(key);
		}
	}
	
	Window::Window(int width, int height, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share)
	{
		VSTM_TRACE_LOGINFO("Window constructed");
		glfwInit();
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//^^feel like this is important, look at what it is later
		m_pwindow = glfwCreateWindow(width, height, title, monitor, share);
		
		if (m_pwindow == NULL)
		{
			VSTM_DEBUG_LOGCRITICAL("glfwCreateWindow failed\n");
			glfwTerminate();
			return;
		}

		glfwSetKeyCallback(m_pwindow, keyCallback);
		glfwSetWindowUserPointer(m_pwindow, reinterpret_cast<void*>(this));
		glfwMakeContextCurrent(m_pwindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VSTM_DEBUG_LOGCRITICAL("Failed to initialize glad\n");
			return;
		}
	}

	Window::~Window()
	{
		VSTM_TRACE_LOGINFO(" Window destructed");
		glfwTerminate();
	}

	void Window::Update()
	{
		m_keys_pressed.reset();
	}

	bool Window::IsClosed()
	{
		return glfwWindowShouldClose(m_pwindow);
	}

	bool Window::KeyPressed(int key)
	{
		return m_keys_pressed[key];
	}

	bool Window::KeyHeld(int key)
	{
		return m_keys_held[key];
	}

	void Window::OnKeyPressed(int key)
	{
		m_keys_pressed[key] = true;
	}

	void Window::OnKeyHeld(int key)
	{
		m_keys_held[key] = true;
	}

	void Window::OnKeyRelease(int key)
	{
		m_keys_held[key] = false;
	}



}