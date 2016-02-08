
#include "Context.hpp"

namespace xe { namespace cm {
	Context::~Context() {}

    ProgramPtr Context::createProgram(ProgramModulePtr module) {
        ProgramPtr program = this->createProgram();
        
        program->add(std::move(module));
        
        return program;
    }
}}
