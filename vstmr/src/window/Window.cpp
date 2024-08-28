#include <glad/glad.h>

#include "Window.h"
#include "diagnostics/Error.h"
#include "diagnostics/Openglerror.h"
#include "diagnostics/Logger.h"

// Callbacks
namespace vstmr {

	void keyCallback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
	{
		vstmr::Window* window = reinterpret_cast<vstmr::Window*>(glfwGetWindowUserPointer(glfwwindow));
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
		vstmr::Window* window = reinterpret_cast<vstmr::Window*>(glfwGetWindowUserPointer(glfwwindow));
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
		vstmr::Window* window = reinterpret_cast<vstmr::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mousex = static_cast<float>(xpos);
			window->m_mousey = static_cast<float>(ypos);
		}
	}

	void scrollWheelCallback(GLFWwindow* glfwwindow, double xoffset, double yoffset)
	{
		vstmr::Window* window = reinterpret_cast<vstmr::Window*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_scrollx = static_cast<float>(xoffset);
			window->m_scrolly = static_cast<float>(yoffset);
		}
	}

	void frameBufferSizeCallback(GLFWwindow* glfwwindow, int width, int height)
	{
		vstmr::Window* window = reinterpret_cast<vstmr::Window*>(glfwGetWindowUserPointer(glfwwindow));
		window->m_viewport.UpdateViewport();
		window->m_width = width;
		window->m_height = height;
	}
}

// Actual Window functions
namespace vstmr {
	
	Window::Window(int width, int height, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share) :
		m_width{ width }, m_height{ height }, m_viewport{ 0, 0, width, height, this }
	{
		VSTM_TRACE_LOGINFO("Window constructed");
		;
		if (!glfwInit())
		{
			VSTM_CD_LOGCRITICAL("GLFW initialization failed");
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
		m_viewport.GetFrameBuffer().Init(); //needs glad to have been loaded done by InitOpengl
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
		m_mouse_changex = m_mousex - m_last_mousex;
		m_mouse_changey = m_last_mousey - m_mousey;
		m_last_mousex = m_mousex;
		m_last_mousey = m_mousey;
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

	bool Window::KeyPressed(int key)
	{
		return m_keys_pressed[key];
	}

	bool Window::KeyHeld(int key)
	{
		return m_keys_held[key];
	}

	float Window::GetMouseX()
	{
		return m_mousex;
	}

	float Window::GetMouseY()
	{
		return m_mousey;
	}

	float Window::GetMouseChangeX()
	{
		return m_mouse_changex;
	}

	float Window::GetMouseChangeY()
	{
		return m_mouse_changey;
	}

	float Window::GetScrollX()
	{
		double scrollx = m_scrollx;
		m_scrolly = 0.0;
		return scrollx;
	}

	float Window::GetScrollY()
	{
		double scrollx = m_scrolly;
		m_scrolly = 0.0;
		return scrollx;
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

	bool Window::MouseButtonPressed(int button)
	{
		return m_mouse_pressed[button];
	}

	bool Window::MouseButtonHeld(int button)
	{
		return m_mouse_held[button];
	}

	void Window::DisableCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::DefaultCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
		CheckOpenGLError();
	}

	GLFWwindow* Window::GetGLFWWindow() 
	{ 
		return m_pwindow; 
	}

	Viewport& Window::GetViewport()
	{
		return m_viewport;
	}

}