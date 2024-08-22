#include <string>

#include "OpenglError.h"
#include "diagnostics/Logger.h"

namespace vstm {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam)
    {
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            VSTM_DEBUG_LOGERROR("OpenGL Error\n{0}\nType: {1}\nSeverity: {2}\nMessage: {3}\n",
                (const char*)userParam, type, severity, message);
            VSTM_CON_LOGERROR("OpenGL Error\n{0}\nType: {1}\nSeverity: {2}\nMessage: {3}\n",
                (const char*)userParam, type, severity, message);
        }
    }

    unsigned int FunctionToCheckOpenGLError(const char* msg)
    {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR)
        {
            switch (errorCode)
            {
                case GL_INVALID_ENUM:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_ENUM\nThe enumeration parameter is not legal for that function.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_INVALID_VALUE:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_VALUE\nNumeric value is not a legal value for that function.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_INVALID_OPERATION:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_OPERATION\nThe specified operation is not allowed in the current state.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_STACK_OVERFLOW:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_STACK_OVERFLOW\nStack pushing operation cannot be done because it would overflow the limit of that stack's size.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_STACK_UNDERFLOW:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_STACK_UNDERFLOW\nStack popping operation cannot be done because the stack is already at its lowest point.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_OUT_OF_MEMORY:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_OUT_OF_MEMORY\nOut of memory when performing an operation. Undefined behaviour invoked.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_FRAMEBUFFER_OPERATION\nAttempting to read or write from an incomplete frame buffer (look up frame buffer completeness)\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                case GL_CONTEXT_LOST:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_CONTEXT_LOST\nThe OpenGL context has been lost, due to a graphics card reset.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
                default:
                {
                    VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. UNKNOWN\nAn unknown OpenGL error occurred.\nFrom VSTM function: {}\n", errorCode, msg);
                    break;
                }
            }
        }

        return errorCode;
    }

}

