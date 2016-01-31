
#pragma once

#ifndef __xe_cm_program_hpp__
#define __xe_cm_program_hpp__

#include <memory>
#include <xe/Object.hpp>
#include <xe/cm/ProgramModule.hpp>

namespace xe { namespace cm {
    class EXENGAPI Program : public Object {
    public:
        virtual ~Program();
        
        virtual void add(ProgramModulePtr module) = 0;
        virtual void link() = 0;
        
        virtual bool isLinked() const = 0;
        virtual std::string getName() = 0;
    };
    
    typedef std::unique_ptr<Program> ProgramPtr;
}}

#endif // __xe_cm_program_hpp__
