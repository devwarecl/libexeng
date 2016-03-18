
#pragma once

#ifndef __xe_cm_imagecl_hpp__
#define __xe_cm_imagecl_hpp__

#include <xe/gfx/Image.hpp>
#include <CL/cl-xe.hpp>

namespace xe { namespace cm {
    
    class ImageCL : public xe::gfx::Image {
    public:
        ImageCL(cl::Context& context, cl_GLuint textureId);
        
        virtual ~ImageCL();
        
        virtual Buffer* getBuffer() override;

		virtual const Buffer* getBuffer() const override;

		virtual xe::gfx::ImageType::Enum getType() const override;

		virtual xe::gfx::PixelFormat::Enum getFormat() const override;

		virtual Vector3i getSize() const override;
		
		virtual TypeInfo getTypeInfo() const override;
		
		cl::Image2DGL& getWrapped() {
            return image;
        }
        
        const cl::Image2DGL& getWrapped() const {
            return image;
        }
        
	private:
        cl::Image2DGL image;
    };
}}

#endif
