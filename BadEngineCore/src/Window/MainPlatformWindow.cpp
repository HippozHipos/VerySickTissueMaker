#include <glad/glad.h>

#include "MainPlatformWindow.h"
#include "Diagnostics/Error.h"
#include "Diagnostics/Openglerror.h"
#include "Diagnostics/Logger.h"

namespace be {

	// Callbacks
	void keyCallback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods)
	{
		be::MainPlatformWindow* window = reinterpret_cast<be::MainPlatformWindow*>(glfwGetWindowUserPointer(glfwwindow));
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
		be::MainPlatformWindow* window = reinterpret_cast<be::MainPlatformWindow*>(glfwGetWindowUserPointer(glfwwindow));
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
		be::MainPlatformWindow* window = reinterpret_cast<be::MainPlatformWindow*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mouse.OnMouseMove(xpos, ypos);
		}
	}

	void scrollWheelCallback(GLFWwindow* glfwwindow, double xoffset, double yoffset)
	{
		be::MainPlatformWindow* window = reinterpret_cast<be::MainPlatformWindow*>(glfwGetWindowUserPointer(glfwwindow));
		if (window)
		{
			window->m_mouse.OnMouseScroll(xoffset, yoffset);
		}
	}

	void frameBufferSizeCallback(GLFWwindow* glfwwindow, int width, int height)
	{
		be::MainPlatformWindow* window = reinterpret_cast<be::MainPlatformWindow*>(glfwGetWindowUserPointer(glfwwindow));
		glViewport(0,0, width, height);
		window->m_width = width;
		window->m_height = height;
	}

    //Window functions

	MainPlatformWindow::MainPlatformWindow(int width, int height, const char* title, Keyboard& keyboard, Mouse& mouse,
		GLFWmonitor* monitor, GLFWwindow* share) :
		m_keyboard{ keyboard }, m_mouse{ mouse },
		m_width{ width }, m_height{ height }
	{
		BELOG_TRC_INFO("Window constructed");
		;
		if (!glfwInit())
		{
			BELOG_CD_ERR("GLFW initialization failed");
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

	void MainPlatformWindow::Update()
	{
		m_keyboard.ResetKeysPressed();
		m_mouse.Update();
		glfwSwapBuffers(m_pwindow);
	}

	void MainPlatformWindow::SetFocus()
	{
		glfwFocusWindow(m_pwindow);
	}

	bool MainPlatformWindow::IsClosed()
	{
		return glfwWindowShouldClose(m_pwindow);
	}

	float MainPlatformWindow::GetWidth()
	{
		return m_width;
	}

	float MainPlatformWindow::GetHeight()
	{
		return m_height;
	}

	void MainPlatformWindow::SetCursorPos(float x, float y)
	{
		glfwSetCursorPos(m_pwindow, static_cast<double>(x), static_cast<double>(y));
	}

	void MainPlatformWindow::DisableCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void MainPlatformWindow::DefaultCursor()
	{
		glfwSetInputMode(m_pwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void MainPlatformWindow::InitOpengl(int width, int height)
	{
		glfwMakeContextCurrent(m_pwindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			BELOG_CD_ERR("Failed to initialize glad\n");
			return;
		}
		glViewport(0, 0, width, height);
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenglErrorMessageCallback, 0);
		CheckOpenGLError();
	}

	GLFWwindow* MainPlatformWindow::GetGLFWWindow() 
	{ 
		return m_pwindow; 
	}
}