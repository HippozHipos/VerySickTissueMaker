#include "Application.h"
#include "util/Logger.h"
#include "util/Error.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"

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

		while (!m_window.IsClosed() && m_running)
		{
			m_window.Fill(0.2f, 0.3f, 0.3f, 1.0f);

			m_renderer.Render();
			
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
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
