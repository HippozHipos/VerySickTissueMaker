#include "Shaders.h"

namespace vstm {

	Shaders::Shaders(const std::string& vertexSource, const std::string& fragmentSource)
    {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        GLint success;
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
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
		glDeleteProgram(programID);
	}

	void Shaders::Use() const
	{
		glUseProgram(programID);
	}

	GLuint Shaders::GetID() const
	{
		return programID;
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