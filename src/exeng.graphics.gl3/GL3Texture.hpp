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
        GL3Texture( ResourceManager *factory, 
                    TextureType::Enum type, 
                    exeng::Vector3i size, 
                    const ColorFormat &colorFormat);
        
        virtual ~GL3Texture();

        virtual void* lock();
        
        virtual void* lock(TextureCubeMapFace::Enum Face);
        
        virtual void unlock();
        
        virtual TextureType::Enum getType() const;
        
        virtual ColorFormat getColorFormat() const;
        
        virtual exeng::Vector3i geSize() const;
        
        virtual void release();
        
        inline GLuint getTextureId() const {
            return this->textureId;
        }
        
        virtual TypeInfo getTypeInfo() const;
        
        virtual std::uint64_t getHandle() const;
        
        virtual const void* getDataPtr() const;
        
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
