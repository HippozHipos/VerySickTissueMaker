#pragma once

#include "diagnostics/Logger.h"

#include <glad/glad.h>

namespace be {

    void GLAPIENTRY OpenglErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);

}

#ifdef NDEBUG
    #define CheckOpenGLError(msg)
#elif defined (RELEASE_WITH_DEBUG)
    #define CheckOpenGLError() MacroToCheckOpenGLError()
#else
    #define CheckOpenGLError() 
#endif





