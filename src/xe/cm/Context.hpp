
#pragma once

#ifndef __xe_cm_context_hpp__
#define __xe_cm_context_hpp__

#include <memory>
#include <xe/Object.hpp>

#include <xe/cm/Kernel.hpp>
#include <xe/cm/Queue.hpp>
#include <xe/cm/ComputeLanguage.hpp>
#include <xe/cm/Program.hpp>

namespace xe { namespace cm {
    class EXENGAPI Context : public Object {
    public:
        virtual ~Context();
        
        virtual ComputeLanguage::Enum getLanguage() const = 0;
        
        virtual Buffer::Ptr createBuffer(Queue *queue, const int size, const void *data = nullptr) = 0;
        
        virtual ProgramModulePtr createProgramModule(const std::string &source) = 0;
        
        virtual ProgramPtr createProgram() = 0;
        
        ProgramPtr createProgram(ProgramModulePtr module);
        
        ProgramPtr createProgram(const std::string &source);
        
        template<typename ProgramModuleCollection>
        ProgramPtr createProgram(ProgramModuleCollection collection) {
            ProgramPtr program = this->createProgram();
            
            for (ProgramModulePtr module : collection) {
                program->add(std::move(module));
            }
            
            program->link();
            
            return program;
        }
        
        virtual KernelPtr createKernel(const Program* program, const std::string &kernel_name) = 0;
        
        virtual QueuePtr createQueue() = 0;        
    };

    typedef std::unique_ptr<Context> ContextPtr;    
}}

#endif
