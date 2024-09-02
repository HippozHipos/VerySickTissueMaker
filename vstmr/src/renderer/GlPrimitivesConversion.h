#pragma once

#include <assert.h>

#include <cstdint>
#include <glad/glad.h>

namespace vstmr {

    template<class Type>
    inline int GlPrimitiveConvert();

    template<class Type>
    inline int GlPrimitiveConvert()
    {
        VSTMR_ASSERT(false, "{} type is not a supported type", typeid(Type).name());
        return 0;
    }

    template<> inline int GlPrimitiveConvert<char>()
    {
        return GL_BYTE;
    }

    template<> inline int GlPrimitiveConvert<unsigned char>()
    {
        return GL_UNSIGNED_BYTE;
    }

    template<> inline int GlPrimitiveConvert<short>()
    {
        return GL_SHORT;
    }

    template<> inline int GlPrimitiveConvert<unsigned short>()
    {
        return GL_UNSIGNED_SHORT;
    }

    template<> inline int GlPrimitiveConvert<int>()
    {
        return GL_INT;
    }

    template<> inline int GlPrimitiveConvert<unsigned int>()
    {
        return GL_UNSIGNED_INT;
    }

    template<> inline int GlPrimitiveConvert<float>()
    {
        return GL_FLOAT;
    }

    template<> inline int GlPrimitiveConvert<double>()
    {
        return GL_DOUBLE;
    }

    size_t GetGLTypeSize(uint32_t type);
}