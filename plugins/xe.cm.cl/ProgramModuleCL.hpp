
#pragma once

#ifndef __xe_cm_programmodulecl_hpp__
#define __xe_cm_programmodulecl_hpp__

#include <CL/cl-xe.hpp>
#include <xe/cm/ProgramModule.hpp>

namespace xe { namespace cm {

    class ProgramModuleCL : public ProgramModule {
    public:
        ProgramModuleCL(const std::string &source);
        ~ProgramModuleCL();
        
        std::string getSource() const {
            return source;
        }
        
    private:
        std::string source;
    };
    
    typedef std::unique_ptr<ProgramModuleCL> ProgramModuleCLPtr;
}}

#endif
