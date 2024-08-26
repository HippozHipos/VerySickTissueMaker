#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#include "Shaders.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	Shaders::Shaders()
    {
		LoadShaderSource(m_vertex_shader_source_path, m_vertex_shader_source);
		LoadShaderSource(m_fragment_shader_source_path, m_fragment_shader_source);

        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, m_vertex_shader_source);
        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_fragment_shader_source);

        m_program_id = glCreateProgram();
        glAttachShader(m_program_id, vertexShader);
        glAttachShader(m_program_id, fragmentShader);
        glLinkProgram(m_program_id);

        GLint success;
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
        if (!success) 
        {
            GLchar infoLog[512];
            VSTM_DEBUG_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", 0, infoLog);
            VSTM_CON_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", 0, infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
		CheckOpenGLError();
    }

	Shaders::~Shaders()
	{
		glDeleteProgram(m_program_id);
		CheckOpenGLError();
	}

	void Shaders::Use() const
	{
		glUseProgram(m_program_id);
		CheckOpenGLError();
	}

	GLuint Shaders::GetID() const
	{
		return m_program_id;
	}

	void Shaders::LoadShaderSource(const char* path, std::string& source)
	{
		std::ifstream inStream{ path };
		if (errno != 0)
		{
			VSTM_CD_LOGERROR("[VSTM Error]Error code: {}\nError description: {}\n", errno, strerror(errno));
		}
		std::ostringstream oss;
		oss << inStream.rdbuf();
		source = oss.str();
	}

	const std::string& Shaders::VertexShaderSource()
	{
		return m_vertex_shader_source;
	}

	const std::string& Shaders::FragmentShaderSource()
	{
		return m_fragment_shader_source;
	}


	void Shaders::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
		CheckOpenGLError();
	}

	void Shaders::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
		CheckOpenGLError();
	}

	void Shaders::SetMat4f(const std::string& name, glm::mat4 value, bool transpose) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, transpose, glm::value_ptr(value));
		CheckOpenGLError();
	}

	GLuint Shaders::CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			VSTM_DEBUG_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", 0, infoLog);
			VSTM_CON_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}\n", 0, infoLog);
		}
		CheckOpenGLError();
		return shader;
	}

}