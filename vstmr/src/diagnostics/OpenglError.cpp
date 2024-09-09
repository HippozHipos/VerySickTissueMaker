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
        VSTM_CD_LOGINFO("{}, [GL Callback]: Type = {}, severity = {}, message = {}\n",
            (type == GL_DEBUG_TYPE_ERROR ? "ERROR" : "INFO"),
            type, severity, message);

        //stderr, "[GL Error Callback]: %s type = 0x%x, severity = 0x%x, message = %s\n",
        //    (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        //    type, severity, message)
    }

}

