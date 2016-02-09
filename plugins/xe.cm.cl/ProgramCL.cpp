
#include "ProgramCL.hpp"

#include <xe/Exception.hpp>

namespace xe { namespace cm {
    ProgramCL::ProgramCL(const cl::Context &context_, const cl::Device &device_) {
        device = device_;
        context = context_;
    }

    ProgramCL::~ProgramCL() {}

    void ProgramCL::add(ProgramModulePtr module_) {
        ProgramModulePtr module = std::move(module_);
        ProgramModuleCLPtr module_cl = ProgramModuleCLPtr(static_cast<ProgramModuleCL*>(module.release()));
        
        modules.push_back(module_cl->getSource());
    }
    
    void ProgramCL::link() {
    
        cl::Program program;
    
        try {
            cl::Program::Sources sources;
            for (const std::string &module : modules) {
                sources.push_back({module.c_str(), module.size()});
            }
    
            program = cl::Program(context, sources);
            program.build();
            
            this->program = program;
            
        } catch (const std::exception &exp) {
            EXENG_THROW_EXCEPTION(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device));
        }
    }
    
    bool ProgramCL::isLinked() const {
        return program()!=nullptr;
    }    
}}
