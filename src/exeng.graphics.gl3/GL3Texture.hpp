/**
 * @file GL3Texture.hpp
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

#include <exeng/HeapBuffer.hpp>
#include <exeng/graphics/Texture.hpp>
#include "GL3.hpp"

namespace exeng { namespace graphics { namespace gl3 {

    class GL3Texture : public Texture {
    public:
        GL3Texture( TextureType::Enum type, exeng::Vector3i size, const ColorFormat &colorFormat);
        virtual ~GL3Texture();

        virtual void* lock() override;
        virtual void* lock(TextureCubeMapFace::Enum Face) override;
        virtual void unlock() override;
        
        virtual TextureType::Enum getType() const override;
        virtual ColorFormat getColorFormat() const override;
        virtual Vector3i geSize() const override;
        virtual void release() override;
        
        inline GLuint getTextureId() const {
            return this->textureId;
        }
        
        virtual TypeInfo getTypeInfo() const override;
        virtual std::uint64_t getHandle() const override;
        virtual const void* getDataPtr() const override;
        
    private:
        GLuint textureId;
        TextureType::Enum type;
        ColorFormat colorFormat;
        exeng::Vector3i size;
        HeapBuffer buffer;
        void* textureData;
        GLenum textureTarget;
        GLenum internalFormat;
    };

}}}

#endif  //__EXENG_GRAPHICS_GL3_TEXTURE_HPP__
