#pragma once

#include "diagnostics/Logger.h"

namespace vstmr {

#define MacroToCheckOpenGLError()\
    unsigned int errorCode;\
    while ((errorCode = glGetError()) != GL_NO_ERROR)\
    {\
        switch (errorCode)\
        {\
        case GL_INVALID_ENUM:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_ENUM\nThe enumeration parameter is not legal for that function\n", errorCode);\
            break;\
        }\
        case GL_INVALID_VALUE:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_VALUE\nNumeric value is not a legal value for that function\n", errorCode);\
            break;\
        }\
        case GL_INVALID_OPERATION:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_OPERATION\nThe specified operation is not allowed in the current state\n", errorCode);\
            break;\
        }\
        case GL_STACK_OVERFLOW:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_STACK_OVERFLOW\nStack pushing operation cannot be done because it would overflow the limit of that stack's size\n", errorCode);\
            break;\
        }\
        case GL_STACK_UNDERFLOW:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_STACK_UNDERFLOW\nStack popping operation cannot be done because the stack is already at its lowest point\n", errorCode);\
            break;\
        }\
        case GL_OUT_OF_MEMORY:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_OUT_OF_MEMORY\nOut of memory when performing an operation. Undefined behaviour invoked\n", errorCode);\
            break;\
        }\
        case GL_INVALID_FRAMEBUFFER_OPERATION:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_INVALID_FRAMEBUFFER_OPERATION\nAttempting to read or write from an incomplete frame buffer (look up frame buffer completeness)\n", errorCode);\
            break;\
        }\
        case GL_CONTEXT_LOST:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. GL_CONTEXT_LOST\nThe OpenGL context has been lost, due to a graphics card reset\n", errorCode);\
            break;\
        }\
        default:\
        {\
            VSTM_CD_LOGINFO("VSTM OpenGL Error\nError Code: {}. UNKNOWN\nAn unknown OpenGL error occurred\n", errorCode); \
            break; \
        }\
        }\
    }

}

#ifdef NDEBUG
    #define CheckOpenGLError(msg)
#elif defined (RELEASE_WITH_DEBUG)
    #define CheckOpenGLError() MacroToCheckOpenGLError()
#else
    #define CheckOpenGLError() MacroToCheckOpenGLError()
#endif





