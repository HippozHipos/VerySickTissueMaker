#include <glad/glad.h>

#include "Window.h"
#include "diagnostics/Error.h"
#include "diagnostics/Openglerror.h"
#include "diagnostics/Logger.h"

//REMINDER: TEMPORARY SOLUTION, NEED TO CHANGE
#include "renderer/Camera.h"


namespace be {

	// Callbacks
	void keyCallback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
	{
		be::Window* window = reinterpret_cast<be::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window && action == GLFW_PRESS)
		{
			window->m_keyboard.OnKeyPress(key);
			window->m_keyboard.OnKeyHeld(key);
		}
		else if (window && action == GLFW_RELEASE)
		{
			window->m_keyboard.OnKeyRelease(key);
		}
	}

	void mouseButtonCallback(GLFWwindow* glfwwindow, int button, int action, int mods)
	{
		be::Window* window = reinterpret_cast<be::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window && action == GLFW_PRESS)
		{
			window->m_mouse.OnMousePress(button);
			window->m_mouse.OnMouseHeld(button);
		}
		else if (window && action == GLFW_RELEASE)
		{
			window->m_mouse.OnMouseRelease(button);
		}
	}

	void mousePositionCallback(GLFWwindow* glfwwindow, double xpos, double ypos)
	{
		be::Window* window = reinterpret_cast<be::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mouse.OnMouseMove(xpos, ypos);
		}
	}

	void scrollWheelCallback(GLFWwindow* glfwwindow, double xoffset, double yoffset)
	{
		be::Window* window = reinterpret_cast<be::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mouse.OnMouseScroll(xoffset, yoffset);
		}
	}

	void frameBufferSizeCallback(GLFWwindow* glfwwindow, int width, int height)
	{
		be::Window* window = reinterpret_cast<be::Window*>(glfwGetWindowUserPointer(glfwwindow));
		glViewport(0,0, width, height);
		window->m_width = width;
		window->m_height = height;
	}

    //Window functions

	Window::Window(int width, int height, const char* title, Keyboard& keyboard, Mouse& mouse,
		GLFWmonitor* monitor, GLFWwindow* share) :
		m_keyboard{ keyboard }, m_mouse{ mouse },
		m_width{ width }, m_height{ height }
	{
		Log(Logger::ERR, Logger::CON | Logger::DEB, "Window constructed");
		;
		if (!glfwInit())
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "GLFW initialization failed");
			ErrorHandler::AddError(Error::WINDOW_CONSTRUCTION_FAILED, "Couldn't initialize glfw");
			glfwTerminate();
			return;
		}
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

	void Window::Update()
	{
		m_keyboard.ResetKeysPressed();
		m_mouse.Update();
		glfwSwapBuffers(m_pwindow);
	}

	void Window::SetFocus()
	{
		glfwFocusWindow(m_pwindow);
	}

	bool Window::IsClosed()
	{
		return glfwWindowShouldClose(m_pwindow);
	}

	float Window::GetWidth()
	{
		return m_width;
	}

	float Window::GetHeight()
	{
		return m_height;
	}

	void Window::SetCursorPos(float x, float y)
	{
		glfwSetCursorPos(m_pwindow, static_cast<double>(x), static_cast<double>(y));
	}

	void Window::DisableCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::DefaultCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Window::InitOpengl(int width, int height)
	{
		glfwMakeContextCurrent(m_pwindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Log(Logger::ERR, Logger::CON | Logger::DEB, "Failed to initialize glad\n");
			return;
		}
		glViewport(0, 0, width, height);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenglErrorMessageCallback, 0);
		CheckOpenGLError();
	}

	GLFWwindow* Window::GetGLFWWindow() 
	{ 
		return m_pwindow; 
	}
}