#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Vertex 0
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// Vertex 1
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// Vertex 2
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,// Vertex 3
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Vertex 4
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// Vertex 5
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,// Vertex 6
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f // Vertex 7
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
		m_window{ 600, 600, "Very sick tissue maker", nullptr, nullptr }, m_firstMouse{ true }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");

		// This removes the visibility of the cursor
		//glfwSetInputMode(m_window.GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set initial cursor position to the center of the screen
		m_lastX = m_window.GetWidth() / 2.0;
		m_lastY = m_window.GetHeight() / 2.0;
		m_window.SetCursorPos(m_lastX, m_lastY);

		//TEXTURE
		image = stbi_load("C:\\Users\\Rahul\\Downloads\\932907c8781d7feee6b4d11d332c0086.png", &width, &height, &colorchannels, 0);
		stbi_set_flip_vertically_on_load(true);
		GLuint textureid;
		glGenTextures(1, &textureid);
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, textureid);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, 0, image);
		glGenerateMipmap(GL_TEXTURE_2D);
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
		// Keyboard input
		m_renderer.GetCamera().ProcessKeyboardMovement(deltaTime, 
			m_window.KeyHeld(GLFW_KEY_W), m_window.KeyHeld(GLFW_KEY_S),
			m_window.KeyHeld(GLFW_KEY_A), m_window.KeyHeld(GLFW_KEY_D),
			m_window.KeyHeld(GLFW_KEY_LEFT_CONTROL), m_window.KeyHeld(GLFW_KEY_SPACE));

		// Mouse input
		float xoffset = m_window.GetMouseX()- m_lastX;
		float yoffset = m_lastY - m_window.GetMouseY(); // Reversed since y-coordinates go from bottom to top

		m_lastX = m_window.GetMouseX();
		m_lastY = m_window.GetMouseY();

		m_renderer.GetCamera().ProcessMouseMovement(xoffset, yoffset);
		// Reset the cursor to the centre of the screen
		m_window.CenterCursorPos(m_lastX, m_lastY);
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
