
#include "ProgramCL.hpp"

namespace xe { namespace cm {
    ProgramCL::ProgramCL(cl::Context &context_) : context(context_) {
        
    }

    ProgramCL::~ProgramCL() {}

    void ProgramCL::add(ProgramModulePtr module_) {
        ProgramModulePtr module = std::move(module_);
        ProgramModuleCLPtr module_cl = ProgramModuleCLPtr(module.release());
        
        modules.push_back(std::move(module_cl));
    }
    
    void ProgramCL::link() {
        cl::Program program = cl::Program(context, modules);
        
        program.build();
        
        this->program = program;
    }
    
    bool ProgramCL::isLinked() const {
        return program();
    }    
}}
