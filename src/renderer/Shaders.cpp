#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"

namespace vstm {

	Shaders::Shaders(const std::string& vertexSource, const std::string& fragmentSource)
    {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

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
    }

	Shaders::~Shaders()
	{
		glDeleteProgram(m_program_id);
	}

	void Shaders::Use() const
	{
		glUseProgram(m_program_id);
	}

	GLuint Shaders::GetID() const
	{
		return m_program_id;
	}

	void Shaders::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
	}

	void Shaders::SetMat4f(const std::string& name, glm::mat4 value, bool transpose) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, transpose, glm::value_ptr(value));
	}

	GLuint Shaders::compileShader(GLenum type, const std::string& source)
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
		return shader;
	}

}