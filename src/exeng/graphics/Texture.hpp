/**
 * @brief
 */

#ifndef __EXENG_GRAPHICS_TEXTURE_HPP__
#define __EXENG_GRAPHICS_TEXTURE_HPP__

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
        class EXENGAPI Texture : public Object
        {
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
