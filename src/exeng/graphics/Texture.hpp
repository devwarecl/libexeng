/**
 * @brief
 */

#ifndef __EXENG_GRAPHICS_TEXTURE_HPP__
#define __EXENG_GRAPHICS_TEXTURE_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"
#include "PixelFormat.hpp"

namespace exeng
{
    namespace graphics
    {
        /**
         * @brief
         */
        namespace TextureType
        {
            enum Type
            {
                Tex1D,
                Tex2D,
                Tex3D,
                TexCubeMap
            };
        }
        
        
        /**
         * @brief
         */
        namespace TextureCubeMapFace
        {
            enum Type
            {
                PositiveX, NegativeX,
                PositiveY, NegativeY,
                PositiveZ, NegativeZ
            };
        }
        
        
        /**
         * @brief
         */
        class EXENGAPI  Texture : public Object
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
            virtual void* lock(TextureCubeMapFace::Type Face) = 0;
            
            /**
             * @brief
             */
            virtual void unlock() = 0;
            
            /**
             * @brief
             */
            virtual TextureType::Type getTextureType() const = 0;
            
            /**
             * @brief
             */
            virtual ColorFormat::Type getColorFormat() const = 0;
            
            /**
             * @brief
             */
            virtual math::Vector3i getSize() const = 0;
            
            /**
             * @brief
             */
            virtual void buildMipmaps() = 0;
        };
    }
}

#endif
