/**
 * @file TextureGL3.hpp
 * @brief Definition of the OpenGL 3 Texture class
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_GL3TEXTURE_HPP__
#define __EXENG_GRAPHICS_GL3_GL3TEXTURE_HPP__

#include <xe/HeapBuffer.hpp>
#include <xe/gfx/Texture.hpp>

#include "GL3.hpp"
#include "TextureBufferGL3.hpp"

namespace xe { namespace gfx { namespace gl3 {

    class TextureGL3 : public Texture {
    public:
        TextureGL3(TextureType::Enum type, Vector3i size, PixelFormat::Enum format, const void *data);
        virtual ~TextureGL3();

		virtual Buffer* getBuffer() override;

		virtual const Buffer* getBuffer() const override;

		virtual Buffer* getBuffer(TextureCubeMapFace::Enum face) override;

		virtual const Buffer* getBuffer(TextureCubeMapFace::Enum face) const override;
        
        virtual TextureType::Enum getType() const override;
        virtual PixelFormat::Enum getFormat() const override;
        virtual Vector3i getSize() const override;
        
        inline GLuint getTextureId() const {
            return this->textureId;
        }
        
        virtual TypeInfo getTypeInfo() const override;
        virtual int getHandle() const override;

        GLenum getTarget() const {
            return textureTarget;
        }
        
        GLenum getInternalFormat() const {
            return internalFormat;
        }
        
    private:
        GLuint textureId;
        TextureType::Enum type;
        PixelFormat::Enum format;
        xe::Vector3i size;
        GLenum textureTarget;
        GLenum internalFormat;
		TextureBufferGL3 buffer;
    };
}}}

#endif  //__EXENG_GRAPHICS_GL3_TEXTURE_HPP__
