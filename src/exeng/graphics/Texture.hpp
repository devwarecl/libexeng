/**
 * @file Texture.hpp
 * @brief Define the Texture abstract class, and his companion structures.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_TEXTURE_HPP__
#define __EXENG_GRAPHICS_TEXTURE_HPP__

#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/graphics/PixelFormat.hpp>

namespace exeng {
    namespace graphics {
        
        /**
         * @brief Type of texture.
         */
        enum class TextureType {
            Tex1D,
            Tex2D,
            Tex3D,
            TexCubeMap
        };
        
        /**
         * @brief 
         */
        enum class TextureCubeMapFace {
            PositiveX, NegativeX,
            PositiveY, NegativeY,
            PositiveZ, NegativeZ
        };
        
        /**
         * @brief 
         */
        class EXENGAPI Texture : public Object {
        public:
            virtual ~Texture() {}

            /**
             * @brief
             */
            virtual void* lock() = 0;
            
            /**
             * @brief
             */
            virtual void* lock(TextureCubeMapFace Face) = 0;
            
            /**
             * @brief
             */
            virtual void unlock() = 0;
            
            /**
             * @brief
             */
            virtual TextureType getTextureType() const = 0;
            
            /**
             * @brief
             */
            virtual ColorFormat getColorFormat() const = 0;
            
            /**
             * @brief
             */
            virtual exeng::math::Vector3i getSize() const = 0;
            
            /**
             * @brief
             */
            virtual void buildMipmaps() = 0;
        };
    }
}

#endif  // __EXENG_GRAPHICS_TEXTURE_HPP__
