#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "util/Logger.h"

namespace vstm {

    class Shaders
    {
    public:
        Shaders(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shaders();

    public: 
        void Use() const;
        GLuint GetID() const;
        void SetFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetMat4f(const std::string& name, glm::mat4 value, bool transpose = false) const;

    private:
        GLuint compileShader(GLenum type, const std::string& source);

    private:
        GLuint m_program_id;

    };

}