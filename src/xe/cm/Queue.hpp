
#pragma once

#ifndef __xe_cm_queue_hpp__
#define __xe_cm_queue_hpp__

#include <memory>
#include <xe/Vector.hpp>
#include <xe/Object.hpp>
#include <xe/cm/Kernel.hpp>

namespace xe { namespace cm {
    class EXENGAPI Queue : public Object {
    public:
        virtual ~Queue();
        
        virtual void enqueueKernel(const Kernel *kernel, const Vector3i &size, const Vector3i &local, const Vector3i &offset) = 0;
        
        virtual void enqueueReadBuffer(const Buffer *buffer, const int offset, const int readSize, void* data) = 0;
        
        virtual void enqueueWriteBuffer(Buffer *buffer, const int offset, const int writeSize, const void* data) = 0;
        
        virtual void wait() = 0;
    };
    
    typedef std::unique_ptr<Queue> QueuePtr;
}}

#endif
