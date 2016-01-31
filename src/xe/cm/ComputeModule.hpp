
#pragma once

#ifndef __xe_cm_computemodule_hpp__
#define __xe_cm_computemodule_hpp__

#include <memory>
#include <xe/Config.hpp>
#include <xe/Buffer.hpp>
#include <xe/cm/Kernel.hpp>
#include <xe/cm/ProgramModule.hpp>
#include <xe/cm/Program.hpp>
#include <xe/cm/Queue.hpp>
#include <xe/cm/ComputeLanguage.hpp>

namespace xe { namespace cm {
    
    class EXENGAPI ComputeModule {
    public:
        virtual ~ComputeModule();
        
        virtual ComputeLanguage::Enum getLanguage() const = 0;
        
        virtual BufferPtr createBuffer(const int size) = 0;
        virtual BufferPtr createBuffer(const int size, const void *data) = 0;
        
        virtual ProgramModulePtr createProgramModule(const std::string &source) = 0;
        
        virtual ProgramPtr createProgram() = 0;
        
        ProgramPtr createProgram(ProgramModulePtr module);
        
        template<typename ProgramModuleCollection>
        ProgramPtr createProgram(ProgramModuleCollection collection) {
            ProgramPtr program = this->createProgram();
            
            for (ProgramModulePtr module : collection) {
                program->add(std::move(module));
            }
            
            return program;
        }
        
        virtual KernelPtr createKernel(const std::string &kernelName, const Program* program) = 0;
        
        virtual QueuePtr createQueue() = 0;
    };
    
    typedef std::unique_ptr<ComputeModule> ComputeModulePtr;
}}

#endif
