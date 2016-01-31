
#pragma once

#ifndef __xe_cm_program_module_hpp__
#define __xe_cm_program_module_hpp__

#include <memory>
#include <xe/Object.hpp>

namespace xe { namespace cm {
    class EXENGAPI ProgramModule : public Object {
    public:
        virtual ~ProgramModule();
    };
    
    typedef std::unique_ptr<ProgramModule> ProgramModulePtr;
}}

#endif // __xe_cm_program_hpp__
