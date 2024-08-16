#include "OpenglError.h"
#include "util/Logger.h"

#include <iostream>

namespace vstm {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam)
    {
        std::cout << ("res\n");
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            VSTM_DEBUG_LOGERROR("OpenGL Error\n{0}\nType: {1}\nSeverity: {2}\nMessage: {3}\n",
                (const char*)userParam, type, severity, message);
            VSTM_CON_LOGERROR("OpenGL Error\n{0}\nType: {1}\nSeverity: {2}\nMessage: {3}\n",
                (const char*)userParam, type, severity, message);
        }
    }

}