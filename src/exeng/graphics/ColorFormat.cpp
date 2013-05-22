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

namespace exeng {
    namespace graphics {
        
        ColorFormat::ColorFormat() : size(0) {
        }
        
        bool ColorFormat::isValid() const {
            // Check sum
            uint32_t sum = 0;
            
            for(auto channel : this->channels) {
                if (channel.component != ColorComponent::None) {
                    sum += channel.size;
                }
            }
            
            if (sum != this->size) {
                return false;
            }
            
            // Check ordering
            bool noneFound = false;
            
            for(auto channel : this->channels) {
                bool nonNone = channel.component != ColorComponent::None;
                
                if (noneFound == true and nonNone == true) {
                    return false;
                }
                
                if (channel.component == ColorComponent::None) {
                    noneFound = true;
                }
            }
            
            return true;
        }
    }
}
