
#include "BufferCL.hpp"

namespace xe { namespace cm {

    BufferCL::BufferCL(cl::CommandQueue *queue, cl::Context &context, const int cache_size) {
        cl_int errCode = 0;
        this->buffer = cl::Buffer(context, CL_MEM_READ_WRITE, cache_size, nullptr, &errCode);
        this->cache_size = cache_size;
        this->queue = queue;        
    }

    BufferCL::~BufferCL() {}

    int BufferCL::getHandle() const {
        return 0;
    }

    int BufferCL::getSize() const {
        return cache.getSize();
    }

    void* BufferCL::lock(BufferLockMode::Enum mode) {
        if (mode&BufferLockMode::Read) {
            
            
            
            
        }
    
        if (mode&BufferLockMode::Write) {
        
        }
    }

    void BufferCL::unlock() {
        
    }

    const void* BufferCL::lock() const {
        if (cache.getSize() != cache_size) {
            cache.alloc(cache_size);
            
            auto locker = cache.lock();
            queue->enqueueReadBuffer(buffer, CL_TRUE, 0, locker.getSize(), locker.getPointer());
        }
        
        return cache.lock();
    }

    void BufferCL::unlock() const {
        cache.unlock();
    }
}}
