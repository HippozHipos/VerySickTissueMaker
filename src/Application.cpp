#include <iostream>
#include <glad/glad.h>

#include "Application.h"
#include "util/Logger.h"
#include "util/Error.h"

namespace rend {

	int  success;
	char info_log[512];
	unsigned int vertex_shader;
	unsigned int fragment_shader;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int shader_program;

	const char* vertex_shader_string = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragment_shader_string = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	static float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	void ivCheck(unsigned int shader, const char* err_string)
	{
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, info_log);
			VSTM_CON_LOGERROR("%s : %d\n", err_string, info_log);
		}
	}


	// Opengl is a state machine;
	// functions don't work on input, they work on ANY object that is bound. This includes but not limited to colours, buffers (VBO, VAO), objects...etc.
	void genBuffers() 
	{
		// -1. bind Vertex Array Object - this will hold all the attribute pointers pointing to VBO data.
		// Consider this to "contain" VBO's, despite it not doing so in practice.
		glGenVertexArrays(1, &VAO);
		// 0. copy our vertices array in a buffer for OpenGL to use
		glGenBuffers(1, &VBO);															// Make n number of buffer(s) and assign id to buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);												// Binds the VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Copy data into the bound VBO in the gpu
																						//		GL_STREAM_DRAW  : the data is set only once and used by the GPU at most a few times.
																						//		GL_STATIC_DRAW  : the data is set only once and used many times.
																						//		GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
		// 1. then set the vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	// V for vertex
	void genVShaders()
	{
		vertex_shader = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader
		glShaderSource(vertex_shader, 1, &vertex_shader_string, NULL); // Bind the vertex shader/Attach the shader source code to the shader object and compile the shader: 
		glCompileShader(vertex_shader);
	}

	// V for vertex
	void runVShaders()
	{
		genVShaders();
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
		ivCheck(vertex_shader, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");
	}

	void genFShaders()
	{
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_string, NULL);
		glCompileShader(fragment_shader);
	}

	void runFShaders()
	{
		genFShaders();
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
		ivCheck(fragment_shader, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
	}

	void genShaderProgram()
	{
		shader_program = glCreateProgram();
		// Link the shaders
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);
	}

	void runShaderProgram()
	{
		genShaderProgram();
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		ivCheck(shader_program, "ERROR::SHADER::PROGRAM::LINKING_FAILED");
	}
	
	void useProgram()
	{
		// run the shader program and bind VAO
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // TRIANGLE!!!
	}

	void deleteShaders()
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
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

		rend::genBuffers();
		rend::runVShaders();
		rend::runFShaders();
		rend::runShaderProgram();

		while (!m_window.IsClosed() && m_running)
		{
			m_window.Fill(0.2f, 0.3f, 0.3f, 1.0f);

			// Shader start
			rend::useProgram();
			// Shader end
			
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
		rend::deleteShaders();
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
