#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "diagnostics/Logger.h"

namespace vstmr {

    class Shaders
    {
    public:
        Shaders();
        ~Shaders();

    public: 
        void Use() const;
        GLuint GetID() const;
        void LoadShaderSource(const char* path, std::string& source);

    public:
        void SetFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetMat4f(const std::string& name, glm::mat4 value, bool transpose = false) const;

    private:
        GLuint CompileShader(GLenum type, const std::string& source);
        const std::string& VertexShaderSource();
        const std::string& FragmentShaderSource();

    private:
        const char* m_vertex_shader_source_path = "../../../../vstmr/assets/shaders/vertex_shader.shader";
        const char* m_fragment_shader_source_path = "../../../../vstmr/assets/shaders/fragment_shader.shader";
        std::string m_vertex_shader_source;
        std::string m_fragment_shader_source;

        GLuint m_program_id;
    };

}