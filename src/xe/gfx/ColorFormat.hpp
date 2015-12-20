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


#ifndef __EXENG_GRAPHICS_COLORFORMAT_HPP__
#define __EXENG_GRAPHICS_COLORFORMAT_HPP__

#include <cstdint>
#include <xe/Config.hpp>

namespace xe { namespace gfx {
            
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
    struct EXENGAPI ColorChannel {
        ColorComponent component;   //! The color channel
        uint16_t size;              //! The size in bits, of the color channel
        
        inline ColorChannel() : 
            component(ColorComponent::None), size(0) {
        }
        
        
        inline ColorChannel(ColorComponent c, uint16_t s) : 
            component(c), size(s) {
        }
        
        
        inline bool operator== (const ColorChannel &other) const {
            if (this->component != other.component) {
                return false;
            }
            
            if (this->size != other.size) {
                return false;
            }
            
            return true;
        }
        
        
        inline bool operator!= (const ColorChannel &other) const {
            return ! (*this == other);
        }
        
        
        inline bool operator< (const ColorChannel &other) const {
            if (this->size >= other.size) {
                return false;
            }
            
            return this->component < other.component;
        }


        inline bool operator>= (const ColorChannel &other) const {
            return ! (*this < other);
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
        * The default state consists only on a empty color format, 
        * and it's not valid.
        */
        ColorFormat();
        ColorFormat(uint16_t size, 
                    const ColorChannel &c1 = ColorChannel(ColorComponent::None, 0), 
                    const ColorChannel &c2 = ColorChannel(ColorComponent::None, 0), 
                    const ColorChannel &c3 = ColorChannel(ColorComponent::None, 0), 
                    const ColorChannel &c4 = ColorChannel(ColorComponent::None, 0));
        
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
        
        bool operator== (const ColorFormat &other) const;
        bool operator!= (const ColorFormat &other) const;
        
        bool operator< (const ColorFormat &other) const;
        
        // Predefined color formats
        static const ColorFormat getR8G8B8A8();
        static const ColorFormat getR5G6B5();
        static const ColorFormat getR5G5B5X1();
    };
}}

#endif // __EXENG_GRAPHICS_COLOR_FORMAT_HPP__
