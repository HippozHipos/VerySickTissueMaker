#include "OpenglError.h"
#include "diagnostics/Logger.h"

namespace be {

    void GLAPIENTRY OpenglErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam)
    {
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            Log(Logger::ERR, Logger::CON | Logger::DEB,
                "[GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
        else
        {
            Log(Logger::INFO, Logger::TRC,
                "[GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
    }

}

