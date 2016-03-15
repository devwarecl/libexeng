
#pragma once 

#ifndef __computeinteropapp_hpp__
#define __computeinteropapp_hpp__

#include <xe/Application.hpp>
#include <xe/cm/ComputeModule.hpp>

class ComputeInteropApplication : public xe::Application {
public:
    ComputeInteropApplication();
    
    xe::cm::Device* findDevice() const;
    
    virtual int run(int argc, char **argv) override;
    
private:
    xe::cm::ComputeModulePtr compute;
    xe::cm::ContextPtr context;
    xe::cm::QueuePtr queue;
    xe::cm::ProgramPtr program;
    xe::cm::KernelPtr kernel_add;
};

#endif __computeinteropapp_hpp__
