
#pragma once

#ifndef __xe_cm_programcl_hpp__
#define __xe_cm_programcl_hpp__

#include <vector>
#include <CL/cl-xe.hpp>
#include <xe/cm/Program.hpp>

#include "ProgramModuleCL.hpp"

namespace xe { namespace cm {

    class ProgramCL : public Program {
    public:
        explicit ProgramCL(const cl::Context &context, const cl::Device &device);
        virtual ~ProgramCL();
        
        virtual void add(ProgramModulePtr module) override;
        virtual void link() override;
        
        virtual bool isLinked() const override;
        
        cl::Program& getWrapped() {
            return program;
        }
        
        const cl::Program& getWrapped() const {
            return program;
        }
        
    private:
        cl::Device device;
        cl::Context context;
        cl::Program program;
        std::vector<std::string> modules;
    };
}}

#endif
