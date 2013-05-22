/**
 * @file ColorFormat.hpp
 * @brief Definition of the ColorFormat structure
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_COLOR_FORMAT_HPP__
#define __EXENG_GRAPHICS_COLOR_FORMAT_HPP__

#include <cstdint>
#include <exeng/Config.hpp>

namespace exeng {
    namespace graphics {
        
        /**
         * @brief The different color channels
         */
        enum class ColorComponent {
            None, Luminance,
            Red,  Green, Blue, Alpha, 
            Unused
        };
        
        /**
         * @brief The ColorChannel struct
         */
        struct ColorChannel {
            ColorComponent component;   //! The color channel
            uint16_t size;              //! The size in bits, of the color channel
            
            inline ColorChannel() : 
                component(ColorComponent::None), size(0) {
            }
            
            inline ColorChannel(ColorComponent c, uint16_t s) : 
                component(c), size(s) {
            }
        };
        
        /**
         * @brief Describes the format of a color used in images, textures
         * and framebuffers.
         */
        struct EXENGAPI ColorFormat {
            
            //! The maximun channel count
            static const int ChannelCount = 4;
            
            //! Pixel storage wide, in bits
            uint16_t size;          

            //! The color channels, specified in order.
            ColorChannel channels[ChannelCount];
            
            /**
             * @brief Initializes the color format to a default state.
             *
             * The default state consists only on a empty color format.
             */
            ColorFormat();
            
            /**
             * @brief Check if the color format is valid
             *
             * The color format is valid only if:
             *
             * - Have at least one color component of type non-none and non-unused.
             * - The sum of its size components is exactly 'size'.
             * 
             * @return 'true' if the color format is valid, and false 
             * in the contrary case.
             */
            bool isValid() const;
        };
    }
}

#endif // __EXENG_GRAPHICS_COLOR_FORMAT_HPP__
