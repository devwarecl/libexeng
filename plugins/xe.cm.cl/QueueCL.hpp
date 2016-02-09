
#pragma once

#ifndef __xe_cm_queuecl_hpp__
#define __xe_cm_queuecl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/Queue.hpp>

namespace xe { namespace cm {
    class QueueCL : public Queue {
    public:
        QueueCL(cl::Context &context);

        virtual ~QueueCL();

        virtual void enqueueKernel(const Kernel *kernel, const int size, const int local, const int offset) override;

        virtual void enqueueKernel(const Kernel *kernel, const Vector2i &size, const Vector2i &local, const Vector2i &offset) override;

        virtual void enqueueKernel(const Kernel *kernel, const Vector3i &size, const Vector3i &local, const Vector3i &offset) override;
        
        virtual void enqueueReadBuffer(const Buffer *buffer, const int offset, const int readSize, void* data) override;
        
        virtual void enqueueWriteBuffer(Buffer *buffer, const int offset, const int writeSize, const void* data) override;
        
        virtual void wait() override;

        cl::CommandQueue& getWrapped() {
            return queue;
        }
        
        const cl::CommandQueue& getWrapped() const {
            return queue;
        }
        
    private:
        cl::Context &context;
        cl::CommandQueue queue;
        cl::Event event;
    };
}}

#endif
