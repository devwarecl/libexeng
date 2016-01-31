
#pragma once

#ifndef __xe_cm_kernel_hpp__
#define __xe_cm_kernel_hpp__

#include <memory>
#include <xe/Config.hpp>
#include <xe/Buffer.hpp>

namespace xe { namespace cm {
    class EXENGAPI Kernel {
    public:
        virtual ~Kernel();
        
        virtual void setArg(const int index, const Buffer *buffer) = 0;        
        virtual void setArg(const int index, const int size, const void *data) = 0;
        
        template<typename BasicType>
        void setArg(const int index, BasicType value) {
            this->setArg(index, sizeof(BasicType), &value);
        }
    };
    
    typedef std::unique_ptr<Kernel> KernelPtr;
}}

#endif
