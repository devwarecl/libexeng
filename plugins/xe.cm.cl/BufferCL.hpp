
#pragma once

#ifndef __xe_cm_buffercl_hpp__
#define __xe_cm_buffercl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/HeapBuffer.hpp>

#include "QueueCL.hpp"

namespace xe { namespace cm {

    class BufferCL : public Buffer {
    public:
        explicit BufferCL(cl::CommandQueue *queue, const int cache_size);
    
        virtual ~BufferCL();

		virtual int getHandle() const override;

		virtual int getSize() const override;

        virtual void* lock(BufferLockMode::Enum mode) override;

		virtual void unlock() override;

		virtual const void* lock() const override;

		virtual void unlock() const override;

    private:
        cl::Buffer buffer;
        cl::CommandQueue *queue = nullptr;
        xe::HeapBuffer cache;
        void* cache_ptr = nullptr;
        int cache_size = 0;
    };
}}

#endif
