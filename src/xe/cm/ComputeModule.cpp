
#include "ComputeModule.hpp"

namespace xe { namespace cm {

    ComputeModule::~ComputeModule() {}
    
    ProgramPtr ComputeModule::createProgram(ProgramModulePtr module) {
        ProgramPtr program = this->createProgram();
        
        program->add(std::move(module));
        
        return program;
    }
}}
