
#include "ProgramCL.hpp"

namespace xe { namespace cm {
    ProgramCL::ProgramCL(cl::Context &context_) : context(context_) {}

    ProgramCL::~ProgramCL() {}

    void ProgramCL::add(ProgramModulePtr module_) {
        ProgramModulePtr module = std::move(module_);
        ProgramModuleCLPtr module_cl = ProgramModuleCLPtr(static_cast<ProgramModuleCL*>(module.release()));
        
        modules.push_back(module_cl->getSource());
    }
    
    void ProgramCL::link() {
		cl::Program::Sources sources;
		for (const std::string &module : modules) {
			sources.push_back({module.c_str(), module.size()});
		}

        cl::Program program = cl::Program(context, sources);
        
        program.build();
        
        this->program = program;
    }
    
    bool ProgramCL::isLinked() const {
        return program()!=nullptr;
    }    
}}
