#include <glad/glad.h>

#include "Window.h"
#include "diagnostics/Error.h"
#include "diagnostics/Openglerror.h"
#include "diagnostics/Logger.h"

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
		else if (window && action == GLFW_RELEASE)
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
		else if (window && action == GLFW_RELEASE)
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

	void frameBufferSizeCallback(GLFWwindow* glfwwindow, int width, int height)
	{
		vstm::Window* window = reinterpret_cast<vstm::Window*>(glfwGetWindowUserPointer(glfwwindow));
		glViewport(0, 0, width, height);
		window->m_width = width;
		window->m_height = height;
	}
}

// Actual Window functions
namespace vstm {
	
	Window::Window(int width, int height, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share)
		: m_width{ static_cast<double>( width ) }, m_height{ static_cast<double>( height ) } 
	{
		VSTM_TRACE_LOGINFO("Window constructed");
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_pwindow = glfwCreateWindow(width, height, title, monitor, share);
		
		if (m_pwindow == nullptr)
		{
			ErrorHandler::AddError(Error::WINDOW_CONSTRUCTION_FAILED, "Couldn't construct window");
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(m_pwindow, reinterpret_cast<void*>(this));
		glfwSetKeyCallback(m_pwindow, keyCallback);
		glfwSetMouseButtonCallback(m_pwindow, mouseButtonCallback);
		glfwSetCursorPosCallback(m_pwindow, mousePositionCallback);
		glfwSetScrollCallback(m_pwindow, scrollWheelCallback);
		glfwSetFramebufferSizeCallback(m_pwindow, frameBufferSizeCallback);
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
		CheckOpenGLError();
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

	double Window::GetScrollX()
	{
		double scrollx = m_scrollx;
		m_scrolly = 0.0;
		return scrollx;
	}

	double Window::GetScrollY()
	{
		double scrollx = m_scrolly;
		m_scrolly = 0.0;
		return scrollx;
	}

	inline double Window::GetWidth()
	{
		return m_width;
	}

	inline double Window::GetHeight()
	{
		return m_height;
	}

	void Window::GetCursorPos(double& xpos, double& ypos)
	{
		glfwGetCursorPos(m_pwindow, &xpos, &ypos);
	}

	void Window::CenterCursorPos(double& last_xpos, double& last_ypos)
	{
		last_xpos = GetWidth() / 2.0;
		last_ypos = GetHeight() / 2.0;
		glfwSetCursorPos(m_pwindow, last_xpos, last_ypos);
	}

	void Window::SetCursorPos(double& last_xpos, double& last_ypos)
	{
		glfwSetCursorPos(m_pwindow, last_xpos, last_ypos);
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
		CheckOpenGLError("Window::InitOpengl");
	}

	GLFWwindow* Window::GetGLFWWindow() 
	{ 
		return m_pwindow; 
	}

}