/**
 * @file ColorFormat.cpp
 * @brief Implementation of the ColorFormat structure methods
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <exeng/graphics/ColorFormat.hpp>

namespace exeng { namespace graphics {
        
    ColorFormat::ColorFormat() : size(0) {
        this->channels[0] = ColorChannel(ColorComponent::None, 0);
    }


    ColorFormat::ColorFormat(uint16_t size, 
                            const ColorChannel &c1, const ColorChannel &c2, 
                            const ColorChannel &c3, const ColorChannel &c4) {
        this->size = size;
        this->channels[0] = c1;
        this->channels[1] = c2;
        this->channels[2] = c3;
        this->channels[3] = c4;
    }


    bool ColorFormat::isValid() const {
        // check size
        if (this->size <= 0) {
            return 0;
        }
        
        // check sum
        uint32_t sum = 0;
        
        for(auto channel : this->channels) {
            if (channel.component != ColorComponent::None) {
                sum += channel.size;
            }
        }
        
        if (sum != this->size) {
            return false;
        }
        
        // check ordering
        bool noneFound = false;
        
        for(auto channel : this->channels) {
            bool nonNone = channel.component != ColorComponent::None;
            
            if (noneFound == true && nonNone == true) {
                return false;
            }
            
            if (channel.component == ColorComponent::None) {
                noneFound = true;
            }
        }
        
        return true;
    }


    bool ColorFormat::operator== (const ColorFormat &other) const {
        if (this->size != other.size) {
            return false;
        }
        
        for (int i=0; i<ColorFormat::ChannelCount; ++i) {
            if (this->channels[i] != other.channels[i]) {
                return false;
            }
        }
        
        return true;
    }


    bool ColorFormat::operator!= (const ColorFormat &other) const {
        return ! (*this == other);
    }


    bool ColorFormat::operator< (const ColorFormat &other) const {
        if (this->size >= other.size) {
            return false;
        }
        
        for (int i=0; i<ColorFormat::ChannelCount; ++i) {
            if ( this->channels[i] >= other.channels[i] ) {
                return false;
            }
        }
        
        return true;
    }

    const ColorFormat ColorFormat::getColorFormatR8G8B8A8() {
        return ColorFormat(
            32, 
            ColorChannel(ColorComponent::Red,   8), 
            ColorChannel(ColorComponent::Green, 8),
            ColorChannel(ColorComponent::Blue,  8),
            ColorChannel(ColorComponent::Alpha, 8)
        );
    }

    const ColorFormat ColorFormat::getColorFormatR5G6B5() {
        return ColorFormat(
            16, 
            ColorChannel(ColorComponent::Red,   5), 
            ColorChannel(ColorComponent::Green, 6),
            ColorChannel(ColorComponent::Blue,  5)
        );
    }

    const ColorFormat ColorFormat::getColorFormatR5G5B5X1() {
        return ColorFormat(
            16, 
            ColorChannel(ColorComponent::Red,   5), 
            ColorChannel(ColorComponent::Green, 5),
            ColorChannel(ColorComponent::Blue,  5),
            ColorChannel(ColorComponent::Unused, 1)
        );
    }

}}
