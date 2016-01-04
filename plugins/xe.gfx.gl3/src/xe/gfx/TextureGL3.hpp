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

namespace xe { namespace gfx { namespace gl3 {

    class TextureGL3 : public Texture {
    public:
        TextureGL3(TextureType::Enum type, Vector3i size, const ColorFormat &format, const void *data);
        virtual ~TextureGL3();

        virtual void* lock() override;
        virtual void* lock(TextureCubeMapFace::Enum Face) override;
        virtual void unlock() override;
        
        virtual TextureType::Enum getType() const override;
        virtual ColorFormat getColorFormat() const override;
        virtual Vector3i getSize() const override;
        
        inline GLuint getTextureId() const {
            return this->textureId;
        }
        
        virtual TypeInfo getTypeInfo() const override;
        virtual int getHandle() const override;
        virtual const void* getDataPtr() const override;
        
    private:
        GLuint textureId;
        TextureType::Enum type;
        ColorFormat format;
        xe::Vector3i size;
        HeapBufferPtr buffer;
        void* textureData;
        GLenum textureTarget;
        GLenum internalFormat;
    };

}}}

#endif  //__EXENG_GRAPHICS_GL3_TEXTURE_HPP__
