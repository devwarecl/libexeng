
#pragma once

#ifndef __xe_cm_memcl_hpp__
#define __xe_cm_memcl_hpp__

#include <CL/cl-xe.hpp>

namespace xe { namespace cm {
    class MemCL {
    public:
        virtual ~MemCL();
        virtual cl::Memory getMemory() = 0;
    };
}}

#endif
