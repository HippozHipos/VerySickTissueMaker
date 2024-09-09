#include <string>

#include "OpenglError.h"
#include "diagnostics/Logger.h"

namespace vstmr {

    void GLAPIENTRY OpenglErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam)
    {
#ifndef NDEBUG
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            VSTM_CD_LOGERROR("ERROR, [GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
        else
        {
            VSTM_TRACE_LOGINFO("INFO, [GL Callback]: Type = {}, severity = {}, message = {}\n",
                type,
                severity,
                message
            );
        }
#endif

        //stderr, "[GL Error Callback]: %s type = 0x%x, severity = 0x%x, message = %s\n",
        //    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        //    type, severity, message)
    }

}

