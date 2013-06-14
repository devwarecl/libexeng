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

#include <exeng/graphics/TextureType.hpp>
#include <exeng/graphics/PixelFormat.hpp>
#include <exeng/graphics/ColorFormat.hpp>

namespace exeng {
    namespace graphics {

        /**
         * @brief 
         */
        enum class TextureCubeMapFace {
            PositiveX, NegativeX,
            PositiveY, NegativeY,
            PositiveZ, NegativeZ
        };
        
        /**
         * @brief Visual specific appearance for materials.
         */
        class EXENGAPI Texture : public Object {
        public:
            virtual ~Texture();

            /**
             * @brief Locks the texture
             */
            virtual void* lock() = 0;
            
            /**
             * @brief Locks the texture
             */
            virtual void* lock(TextureCubeMapFace Face) = 0;
            
            /**
             * @brief Unlocks the texture.
             */
            virtual void unlock() = 0;
            
            /**
             * @brief Get the current type of texture
             */
            virtual TextureType getType() const = 0;
            
            /**
             * @brief Get the color format of the texture
             */
            virtual ColorFormat getColorFormat() const = 0;
            
            /**
             * @brief Get the size, in texels, of the texture.
             */
            virtual exeng::math::Vector3i getSize() const = 0;
        };
    }
}

#endif  // __EXENG_GRAPHICS_TEXTURE_HPP__
