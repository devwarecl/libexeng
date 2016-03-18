
#include "BufferCL_GL.hpp"

#include <cassert>

namespace xe { namespace cm {

    BufferCL_GL::BufferCL_GL(cl::Context context, cl_GLuint bufferId) {
        assert(bufferId);
    
        cl_int errCode = 0;
        buffergl = cl::BufferGL(context, CL_MEM_READ_WRITE, bufferId, &errCode);
        
        assert(errCode);
    }
    
    BufferCL_GL::~BufferCL_GL() {}
    
    int BufferCL_GL::getHandle() const {
        return 0;
    }

    int BufferCL_GL::getSize() const {
        return 0;
    }

    void* BufferCL_GL::lock(BufferUsage::Enum) {
        return nullptr;
    }

    void BufferCL_GL::unlock() {}

    const void* BufferCL_GL::lock() const {
        return nullptr;
    }

    void BufferCL_GL::unlock() const {}
    
    TypeInfo BufferCL_GL::getTypeInfo() const {
        return TypeId<BufferCL_GL>();
    }
}}
