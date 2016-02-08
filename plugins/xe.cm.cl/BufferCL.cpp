
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

    void* BufferCL::lock(BufferUsage::Enum mode) {
        bool sync = false;
        
        if (cache.getSize() != cache_size) {
            cache.alloc(cache_size);
            sync = true;
        }
        
        void* cache_ptr = cache.lock(mode);
        
        if (mode&BufferUsage::Read) {
            // sync the buffer (enable for reading)
            if (sync) {
                queue->enqueueReadBuffer(buffer, CL_TRUE, 0, cache_size, cache_ptr);
            }
        }
    
        if (mode&BufferUsage::Write) {
            this->cache_ptr = cache_ptr;
        }
        
        return cache_ptr;
    }

    void BufferCL::unlock() {
        void *cache_ptr = this->cache_ptr;
        this->cache_ptr = nullptr;
        
        if (cache_ptr) {
            queue->enqueueWriteBuffer(buffer, CL_TRUE, 0, cache_size, cache_ptr);
        }
        
        cache.unlock();
    }

    const void* BufferCL::lock() const {
        return const_cast<BufferCL*>(this)->lock(BufferUsage::Read);
    }

    void BufferCL::unlock() const {
        const_cast<BufferCL*>(this)->unlock();
    }
    
    TypeInfo BufferCL::getTypeInfo() const {
        return TypeId<BufferCL>();
    }
}}
