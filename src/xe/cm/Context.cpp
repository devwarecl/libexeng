
#include "Context.hpp"

namespace xe { namespace cm {
	Context::~Context() {}

    ProgramPtr Context::createProgram(ProgramModulePtr module) {
        ProgramPtr program = this->createProgram();
        
        program->add(std::move(module));
        program->link();
        
        return program;
    }
    
    ProgramPtr Context::createProgram(const std::string &source) {
        return this->createProgram(this->createProgramModule(source));
    }
}}
