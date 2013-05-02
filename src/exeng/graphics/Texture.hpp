/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef exeng_graphics_texture_hpp
#define exeng_graphics_texture_hpp

#include "../Object.hpp"
#include "../math/TVector.hpp"
#include "PixelFormat.hpp"

namespace exeng {
    namespace graphics {
        
        /**
         * @brief
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

#endif
