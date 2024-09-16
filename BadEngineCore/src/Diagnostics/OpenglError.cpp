#include "OpenglError.h"
#include "Diagnostics/Logger.h"

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
            BDLOG_CD_ERR(
                "[GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
        else
        {
            BDLOG_TRC_INFO(
                "[GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
    }

}

