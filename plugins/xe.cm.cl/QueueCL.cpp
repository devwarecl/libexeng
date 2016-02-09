
#include "QueueCL.hpp"

#include "KernelCL.hpp"
#include "BufferCL.hpp"

namespace xe { namespace cm {

    QueueCL::QueueCL(cl::Context &context_) : context(context_) {
        cl::CommandQueue queue = cl::CommandQueue(context, 0);
        
        this->queue = queue;
    }
    
    QueueCL::~QueueCL() {}
    
    void QueueCL::enqueueKernel(const Kernel *kernel, const int size, const int local, const int offset) {
        queue.enqueueNDRangeKernel (
            static_cast<const KernelCL*>(kernel)->getWrapped(),
            (offset>0)?cl::NDRange(offset):cl::NullRange,
            cl::NDRange(size),
            (local>0)?cl::NDRange(local):cl::NullRange
        );
    }
    
    void QueueCL::enqueueKernel(const Kernel *kernel, const Vector2i &size, const Vector2i &local, const Vector2i &offset) {
        queue.enqueueNDRangeKernel (
            static_cast<const KernelCL*>(kernel)->getWrapped(),
            (!offset.isZero())?cl::NDRange(offset.x, offset.y):cl::NullRange,
            cl::NDRange(size.x, size.y),
            (!local.isZero())?cl::NDRange(local.x, local.y):cl::NullRange
        );        
    }

    void QueueCL::enqueueKernel(const Kernel *kernel, const Vector3i &size, const Vector3i &local, const Vector3i &offset) {
        queue.enqueueNDRangeKernel (
            static_cast<const KernelCL*>(kernel)->getWrapped(),
            (!offset.isZero())?cl::NDRange(offset.x, offset.y, offset.z):cl::NullRange,
            cl::NDRange(size.x, size.y, size.z),
            (!local.isZero())?cl::NDRange(local.x, local.y, local.z):cl::NullRange
        );
    }
        
    void QueueCL::enqueueReadBuffer(const Buffer *buffer, const int offset, const int readSize, void* data) {
        queue.enqueueReadBuffer (
            static_cast<const BufferCL*>(buffer)->getWrapped(),
            CL_TRUE,
            offset, 
            readSize, 
            data
        );
    }
        
    void QueueCL::enqueueWriteBuffer(Buffer *buffer, const int offset, const int writeSize, const void* data) {
        queue.enqueueWriteBuffer (
            static_cast<BufferCL*>(buffer)->getWrapped(),
            CL_TRUE,
            offset, 
            writeSize, 
            data
        );
    }
        
    void QueueCL::wait() {
        event.wait();
    }
}}
