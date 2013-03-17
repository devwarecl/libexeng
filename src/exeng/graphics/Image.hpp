
/**
 * @brief Define the engine's basic data types. Also, define fixed-size, elemental platform-independent.
 */

#ifndef __EXENG_GRAPHICS_IMAGE_HPP__
#define __EXENG_GRAPHICS_IMAGE_HPP__

#include "../DataTypes.hpp"
#include "../math/TVector.hpp"
#include "PixelFormat.hpp"
#include "PixelType.hpp"

namespace exeng {
    namespace graphics {
        /**
         * @brief Image class.
         */
        class EXENGAPI Image {
        public:
            Image();
            Image(const math::Vector3i& size, ColorFormat::Type format, PixelType::Type type=PixelType::Integer);
            
            virtual ~Image();
            
            /** 
             * @brief Get a raw pointer to the pixel data
             */
            const void* getPtr() const;
            
            /**
             * @brief Get a raw pointer
             */
            void* getPtr();
            
            /**
             * @brief Get the current image format
             */
            ColorFormat::Type getFormat() const;
            
            /**
             * @brief Get the pixel data type storage
             */
            PixelType::Type getType() const;
            
            /**
             * @brief 
             */
            math::Vector3i getSize() const;
            
            /**
             * @brief 
             */
            void initialize( const math::Vector3i& size, ColorFormat::Type format, PixelType::Type type=PixelType::Integer);
            
            /**
             * @brief 
             */
            UInt32 getPixel(const math::Vector2i& position) const;
            
            /**
             * @brief 
             */
            void setPixel(const math::Vector2i& position, UInt32 color);
            
        private:
            int getOffset(const math::Vector2i& position) const;
            
        private:
            struct Private;
            Private* Data;
        };
    }
}

#endif  //__EXENG_GRAPHICS_IMAGE_HPP__
