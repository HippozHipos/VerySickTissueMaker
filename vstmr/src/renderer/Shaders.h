#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "diagnostics/Logger.h"

namespace vstmr {

    class Shaders
    {
    public:
        Shaders(const char* vertexPath, const char* fragmentPath);
        ~Shaders();

    public: 
        void Use() const;
        GLuint GetID() const;

    public:
        void SetVertexShaderPath(const char* path);
        void SetFragmentShaderPath(const char* path);

        void SetFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetMat4f(const std::string& name, glm::mat4 value, bool transpose = false) const;

    private:
        void LoadShaderSource(const char* path, std::string& source);
        GLuint CompileShader(GLenum type, const std::string& source);
        void MakeProgram();
        const std::string& VertexShaderSource();
        const std::string& FragmentShaderSource();

    private:
        std::string m_vertex_shader_source_path;
        std::string m_fragment_shader_source_path;
        std::string m_vertex_shader_source;
        std::string m_fragment_shader_source;

        GLuint m_program_id;
    };

}