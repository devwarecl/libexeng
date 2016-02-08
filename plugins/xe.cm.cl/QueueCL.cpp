
#include "QueueCL.hpp"

namespace xe { namespace cm {

    QueueCL::QueueCL(cl::Context &context_) : context(context_) {
        cl_int errCode = 0;
        cl::CommandQueue queue = cl::CommandQueue(context, &errCode);
        
        this->queue = queue;
    }

    QueueCL::~QueueCL() {}

    void QueueCL::enqueueKernel(const Kernel *kernel, const Vector3i &size, const Vector3i &local, const Vector3i &offset) {

    }
        
    void QueueCL::enqueueReadBuffer(const Buffer *buffer, const int offset, const int readSize, void* data) {

    }
        
    void QueueCL::enqueueWriteBuffer(Buffer *buffer, const int offset, const int writeSize, const void* data) {

    }
        
    void QueueCL::wait() {
        event.wait();
    }
}}
