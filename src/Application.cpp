#include "Application.h"
#include "util/Logger.h"
#include "util/Error.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"

#include "timer/timer.h"

namespace rend {

	// Vertex data for a cube
	float vertices[] = {
		// Positions          
		-0.5f, -0.5f, -0.5f,  // Vertex 0
		 0.5f, -0.5f, -0.5f,  // Vertex 1
		 0.5f,  0.5f, -0.5f,  // Vertex 2
		-0.5f,  0.5f, -0.5f,  // Vertex 3
		-0.5f, -0.5f,  0.5f,  // Vertex 4
		 0.5f, -0.5f,  0.5f,  // Vertex 5
		 0.5f,  0.5f,  0.5f,  // Vertex 6
		-0.5f,  0.5f,  0.5f   // Vertex 7
	};

	// Indices for drawing the cube using element array
	unsigned int indices[] = {
		// Back face
		0, 1, 2,
		2, 3, 0,

		// Front face
		4, 5, 6,
		6, 7, 4,

		// Left face
		0, 3, 7,
		7, 4, 0,

		// Right face
		1, 2, 6,
		6, 5, 1,

		// Bottom face
		0, 1, 5,
		5, 4, 0,

		// Top face
		3, 2, 6,
		6, 7, 3
	};


	void setup(vstm::Renderer& renderer)
	{
		vstm::VertexBuffer vertexBuffer;
		vstm::IndexBuffer indexBuffer;

		vertexBuffer.Bind();
		vertexBuffer.BufferData(sizeof(vertices));
		vertexBuffer.BufferSubData(vertices, sizeof(vertices), 0);
		
		indexBuffer.Bind();
		indexBuffer.BufferData(sizeof(indices));
		indexBuffer.BufferSubData(indices, sizeof(indices), 0);

		renderer.SetLayout();
	}
}

namespace vstm {

	Application::Application() :
		m_window{ 600, 600, "Very sick tissue maker", nullptr, nullptr }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");

		// This removes the visibility of the cursor
		//glfwSetInputMode(m_window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Get the primary monitor's video mode - for compatability across multiple setups:
		// i.e. Different resolutions, multiple monitors ...etc.
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

		m_screenWidth = mode->width;
		m_screenHeight = mode->height;

		// Set initial cursor position to the center of the screen
		m_lastX = m_screenWidth / 2.0;
		m_lastY = m_screenHeight / 2.0;
		glfwSetCursorPos(m_window.GetGLFWWindow(), m_lastX, m_lastY);
	}

	void Application::Run()
	{
		ErrorHandler::Handle();
		HandleErrorActions();

		rend::setup(m_renderer);
		
		// note that this is allowed, the call to glVertexAttribPointer registered
		// VBO as the vertex attribute's bound vertex buffer object so afterwards 
		// we can safely unbind
		vstm::VertexBuffer::UnBind();

		Timer timer{};

		while (!m_window.IsClosed() && m_running)
		{
			double deltaTime = timer.getDeltaTime();

			m_window.Fill(0.2f, 0.3f, 0.3f, 1.0f);
			
			ProcessInput(deltaTime);
			m_renderer.Render();
			
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
	}

	void Application::ProcessInput(double deltaTime)
	{
		GLFWwindow* window = m_window.GetGLFWWindow();

		// Keyboard input
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 1, 0, 0, 0);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 0, 1, 0, 0);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 0, 0, 1, 0);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 0, 0, 0, 1);

		// Mouse input
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (m_firstMouse)
		{
			m_lastX = xpos;
			m_lastY = ypos;
			m_firstMouse = false;
		}

		float xoffset = xpos - m_lastX;
		float yoffset = m_lastY - ypos; // Reversed since y-coordinates go from bottom to top

		m_lastX = xpos;
		m_lastY = ypos;

		m_renderer.GetCamera().ProcessMouseMovement(xoffset, yoffset);
		// Reset the cursor to the centre of the screen
		CaptureMouse(window);
	}

	void Application::CaptureMouse(GLFWwindow* window)
	{
		m_lastX = m_screenWidth / 2.0;
		m_lastY = m_screenHeight / 2.0;
		glfwSetCursorPos(window, m_lastX, m_lastY);
	}

	void Application::HandleErrorActions()
	{
		for (size_t i = 0; i < ErrorHandler::NumActions(); i++)
		{
			switch (ErrorHandler::GetAction(i))
			{
			case ErrorHandler::TerminateApplication: m_running = false;

			}
		}
	}

}
