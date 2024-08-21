#pragma once

#include "glad/glad.h"

namespace vstm {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);

    unsigned int FunctionToCheckOpenGLError(const char* msg);

}

#ifdef NDEBUG
    #define CheckOpenGLError(msg)
#elif defined (RELEASE_WITH_DEBUG)
    #define CheckOpenGLError(msg) FunctionToCheckOpenGLError(msg)
#else
    #define CheckOpenGLError(msg) FunctionToCheckOpenGLError(msg)
#endif





