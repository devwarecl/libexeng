
#include "Context.hpp"

namespace xe { namespace cm {
    ProgramPtr Context::createProgram(ProgramModulePtr module) {
        ProgramPtr program = this->createProgram();
        
        program->add(std::move(module));
        
        return program;
    }
}}
