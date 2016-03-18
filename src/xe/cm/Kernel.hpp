
#pragma once

#ifndef __xe_cm_kernel_hpp__
#define __xe_cm_kernel_hpp__

#include <memory>
#include <xe/Config.hpp>
#include <xe/Buffer.hpp>
#include <xe/gfx/Forward.hpp>

namespace xe { namespace cm {
    class EXENGAPI Kernel {
    public:
        virtual ~Kernel();
        
        virtual void setArg(const int index, const Buffer *buffer) = 0;        
        virtual void setArg(const int index, const int size, const void *data) = 0;
        virtual void setArg(const int index, const xe::gfx::Image *image) = 0;
    };
    
    typedef std::unique_ptr<Kernel> KernelPtr;
}}

#endif
