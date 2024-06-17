#include <glad/glad.h>

#include "Window.h"
#include "util/Error.h"
#include "util/Logger.h"

// Callbacks
namespace vstm {
	void keyCallback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window && action == GLFW_PRESS)
		{
			window->OnKeyPress(key);
			window->OnKeyHeld(key);
		}
		else //(window && action == GLFW_RELEASE)
		{
			window->OnKeyRelease(key);
		}
	}

	void mouseButtonCallback(GLFWwindow* glfwwindow, int button, int action, int mods)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window && action == GLFW_PRESS)
		{
			window->OnMousePress(button);
			window->OnMouseHeld(button);
		}
		else //(window && action == GLFW_RELEASE)
		{
			window->OnMouseRelease(button);
		}
	}

	void mousePositionCallback(GLFWwindow* glfwwindow, double xpos, double ypos)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mousex = xpos;
			window->m_mousey = ypos;
		}
	}

	void scrollWheelCallback(GLFWwindow* glfwwindow, double xoffset, double yoffset)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_scrollx = xoffset;
			window->m_scrolly = yoffset;
		}
	}

	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}


namespace vstm {
	
	Window::Window(int width, int height, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share)
	{
		VSTM_TRACE_LOGINFO("Window constructed");
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_pwindow = glfwCreateWindow(width, height, title, monitor, share);
		
		if (m_pwindow == nullptr)
		{
			ErrorHandler::AddError(Error::WINDOW_CONSTRUCTION_FAILED, "Couldn't construct window");
			glfwTerminate();
			return;
		}

		glfwSetKeyCallback(m_pwindow, keyCallback);
		glfwSetMouseButtonCallback(m_pwindow, mouseButtonCallback);
		glfwSetCursorPosCallback(m_pwindow, mousePositionCallback);
		glfwSetScrollCallback(m_pwindow, scrollWheelCallback);
		glfwSetWindowUserPointer(m_pwindow, reinterpret_cast<void*>(this));
		InitOpengl(width, height);
	}

	Window::~Window()
	{
		VSTM_TRACE_LOGINFO(" Window destructed");
		glfwTerminate();
	}

	void Window::Update()
	{
		m_keys_pressed.reset();
		m_mouse_pressed.reset();
		glfwSwapBuffers(m_pwindow);
	}

	void Window::Fill(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SetFocus()
	{
		glfwFocusWindow(m_pwindow);
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

	double Window::GetMouseX()
	{
		return m_mousex;
	}

	double Window::GetMouseY()
	{
		return m_mousey;
	}

	bool Window::MouseButtonPressed(int button)
	{
		return m_mouse_pressed[button];
	}

	bool Window::MouseButtonHeld(int button)
	{
		return m_mouse_held[button];
	}

	void Window::OnKeyPress(int key)
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

	void Window::OnMousePress(int button)
	{
		m_mouse_pressed[button] = true;
	}

	void Window::OnMouseHeld(int button)
	{
		m_mouse_held[button] = true;
	}

	void Window::OnMouseRelease(int button)
	{
		m_mouse_held[button] = false;
	}

	void Window::InitOpengl(int width, int height)
	{
		glfwMakeContextCurrent(m_pwindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VSTM_DEBUG_LOGCRITICAL("Failed to initialize glad\n");
			return;
		}
		glViewport(0, 0, width, height);
		glfwSetFramebufferSizeCallback(m_pwindow, FrameBufferSizeCallback);
	}

}