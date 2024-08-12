#pragma once

#include <glad/glad.h>

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

    private:
        GLuint compileShader(GLenum type, const std::string& source);

    private:
        GLuint m_program_id;

    };

}