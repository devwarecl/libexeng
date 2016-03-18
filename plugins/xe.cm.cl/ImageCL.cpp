
#include "ImageCL.hpp"

#include <cassert>

namespace xe { namespace cm {
    
    ImageCL::ImageCL(cl::Context& context, cl_GLuint textureId) {
        assert(textureId);
    
        cl_int errCode = 0;
        
        // TODO: Replace the constant with the correct macro from gl.h
        const int GL_TEXTURE_2D = 0x0DE1;
        
        image = cl::Image2DGL(context, CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, textureId, &errCode);
        
        assert(errCode);
    }
    
    ImageCL::~ImageCL() {}
    
    Buffer* ImageCL::getBuffer() {
        return nullptr;
    }

    const Buffer* ImageCL::getBuffer() const {
        return nullptr;
    }
    
    xe::gfx::ImageType::Enum ImageCL::getType() const {
        return xe::gfx::ImageType::Img2D;
    }

    xe::gfx::PixelFormat::Enum ImageCL::getFormat() const {
        return xe::gfx::PixelFormat::Unknown;
    }

    Vector3i ImageCL::getSize() const {
        return {0, 0, 0};
    }
    
    TypeInfo ImageCL::getTypeInfo() const {
        return TypeId<ImageCL>();
    }
}}
