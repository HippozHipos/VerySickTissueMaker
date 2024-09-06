#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

#include "Shaders.h"
#include "diagnostics/OpenglError.h"

namespace vstmr {

	Shaders::Shaders(const char* vertexPath, const char* fragmentPath)
	{
		m_vertex_shader_source_path = vertexPath;
		m_fragment_shader_source_path = fragmentPath;
		MakeProgram();
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

		if (!inStream.is_open()) 
		{
			VSTM_CD_LOGERROR("[VSTM Error] Error opening file: {}\nError code: {}\nError description: {}\n", path, errno, strerror(errno));
			return;
		}

		std::ostringstream oss;
		oss << inStream.rdbuf();  
		source = oss.str(); 

	}

	void Shaders::SetVertexShaderPath(const char* path)
	{
		m_vertex_shader_source_path = path;
	}

	void Shaders::SetFragmentShaderPath(const char* path)
	{
		m_fragment_shader_source_path = path;
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

	void Shaders::SetMat4f(const std::string& name, const glm::mat4& value, bool transpose) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, transpose, glm::value_ptr(value));
		CheckOpenGLError();
	}

	void Shaders::SetVec3f(const std::string& name, const glm::vec3& value, bool transpose) const
	{
		glUniform3f(glGetUniformLocation(m_program_id, name.c_str()), value.x, value.y, value.z);
		CheckOpenGLError();
	}

	void Shaders::RecompileShader()
	{
		MakeProgram();
	}

	GLuint Shaders::CompileShader(GLenum type, const char* src)
	{
		GLuint shader = glCreateShader(type);
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

	void Shaders::MakeProgram()
	{
		std::string vertex_shader_source;
		std::string fragment_shader_source;

		LoadShaderSource(m_vertex_shader_source_path.c_str(), vertex_shader_source);
		LoadShaderSource(m_fragment_shader_source_path.c_str(), fragment_shader_source);

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertex_shader_source.c_str());
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source.c_str());

		m_program_id = glCreateProgram();
		glAttachShader(m_program_id, vertexShader);
		glAttachShader(m_program_id, fragmentShader);
		glLinkProgram(m_program_id);

		GLint success;
		glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[512];
			VSTM_DEBUG_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}", 0, infoLog);
			VSTM_CON_LOGERROR("[VSTM Error]\nError code: {}\nError description: {}", 0, infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		CheckOpenGLError();
	}

}