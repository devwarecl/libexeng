
#include "KernelCL.hpp"
#include "BufferCL.hpp"
#include "BufferCL_GL.hpp"
#include "ImageCL.hpp"

#include <xe/Exception.hpp>

namespace xe { namespace cm {

    KernelCL::KernelCL(xe::gfx::GraphicsDriver *graphicsDriver_, const cl::Context &context_, const cl::Program &program_, const std::string &kernel_name) {
        graphicsDriver = graphicsDriver_;
        context = context_;
        program = program_;
        kernel = cl::Kernel(program, kernel_name.c_str());
    }
    
    KernelCL::~KernelCL() {}

    void KernelCL::setArg(const int index, const Buffer *buffer) {
        assert(index >= 0);
        assert(buffer);
        
        if (buffer->getTypeInfo() == TypeId<BufferCL>()) {
            auto buffercl = static_cast<const BufferCL*>(buffer)->getWrapped();
            kernel.setArg(index, buffercl);
            
        } else if (buffer->getTypeInfo() == TypeId<BufferCL_GL>()) {
            auto buffercl = static_cast<const BufferCL_GL*>(buffer)->getWrapped();
            kernel.setArg(index, buffercl);
            
        } else {
            assert(false);
        }
    }

    void KernelCL::setArg(const int index, const int size, const void *data) {
        assert(index >= 0);
        assert(size >= 0);
        
        kernel.setArg(index, size, data);
    }
    
    void KernelCL::setArg(const int index, const xe::gfx::Image *image) {
        assert(index >= 0);
        assert(image);
        
        if (image->getTypeInfo() == TypeId<ImageCL>()) {
            auto imagecl = static_cast<const ImageCL*>(image);
        
            kernel.setArg(index, imagecl);
            
        } else {
            assert(false);
        }
    }
}}
