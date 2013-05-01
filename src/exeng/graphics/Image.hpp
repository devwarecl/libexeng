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

/**
 * @brief Define the engine's basic data types. Also, define fixed-size, elemental platform-independent.
 */

#ifndef __EXENG_GRAPHICS_IMAGE_HPP__
#define __EXENG_GRAPHICS_IMAGE_HPP__

#include <cstdint>
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
            Image(const math::Vector3i& size, ColorFormat format, PixelType type=PixelType::Integer);
            
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
            ColorFormat getFormat() const;
            
            /**
             * @brief Get the pixel data type storage
             */
            PixelType getType() const;
            
            /**
             * @brief 
             */
            math::Vector3i getSize() const;
            
            /**
             * @brief 
             */
            void initialize( const math::Vector3i& size, ColorFormat format, PixelType type=PixelType::Integer);
            
            /**
             * @brief 
             */
            std::uint32_t getPixel(const math::Vector2i& position) const;
            
            /**
             * @brief 
             */
            void setPixel(const math::Vector2i& position, std::uint32_t color);
            
        private:
            int getOffset(const math::Vector2i& position) const;
            
        private:
            struct Private;
            Private* Data;
        };
    }
}

#endif  //__EXENG_GRAPHICS_IMAGE_HPP__
