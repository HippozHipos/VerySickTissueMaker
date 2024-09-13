#pragma once

#include "pch.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "diagnostics/Logger.h"

namespace be {

    class Shaders
    {
    public:
        Shaders() = default;
        Shaders(const char* vertexPath, const char* fragmentPath);
        ~Shaders();

    public: 
        void Use() const;
        GLuint GetID() const;

    public:
        void SetVertexShaderPath(const char* path);
        void SetFragmentShaderPath(const char* path);
        void RecompileShader();
        void SetFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetMat4f(const std::string& name, const glm::mat4& value, bool transpose = false) const;
        void SetVec3f(const std::string& name, const glm::vec3& vec3, bool transpose = false) const;

    private:
        void LoadShaderSource(const char* path, std::string& source);
        GLuint CompileShader(GLenum type, const char* src);
        void MakeProgram();

    private:
        std::string m_vertex_shader_source_path;
        std::string m_fragment_shader_source_path;
        GLuint m_program_id = 0;
    };

}