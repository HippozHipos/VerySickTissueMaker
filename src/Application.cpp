#include <iostream>
#include <glad/glad.h>

#include "Application.h"
#include "util/Logger.h"
#include "util/Error.h"
#include "renderer/Renderer.h"

namespace rend {

	int  success;
	char info_log[512];
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	unsigned int VBO, VAO;


	/*const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 1 in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";*/

	/*const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";*/

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, // right 
	 0.0f,  0.5f, 0.0f  // top   
	};

	void shitMain()
	{
		vstm::Renderer renderer{};
		const char* vertexShaderSource = renderer.VertexShaderSource().c_str();
		const char* fragmentShaderSource = renderer.FragmentShaderSource().c_str();

		// build and compile our shader program
		// ------------------------------------
		// vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
		}

		// fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
		}

		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) 
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
	}

	void renderLoop()
	{
		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time 

	}

	void deleshit()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
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

		rend::shitMain();

		while (!m_window.IsClosed() && m_running)
		{
			m_window.Fill(0.2f, 0.3f, 0.3f, 1.0f);

			// Shader start
			rend::renderLoop();
			// Shader end


			
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
		rend::deleshit();
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
