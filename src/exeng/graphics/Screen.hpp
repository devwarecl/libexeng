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

#ifndef exeng_graphics_canvas_hpp
#define exeng_graphics_canvas_hpp

#include <vector>

#include "../Object.hpp"
#include "../math/TSize.hpp"
#include "PixelFormat.hpp"

namespace exeng {
    namespace graphics {
        
        /**
         * @brief Encapsulate a display mode.
         */
        struct DisplayMode {
            DisplayMode() {}
            
            DisplayMode(const exeng::math::Size2i &size, PixelFormat format) {
                this->size = size;
                this->format = format;
                this->frequency = 0;
                this->fullscreen = false;
            }
            
            exeng::math::Size2i size;   //! Width and height
            PixelFormat format;         //! Color format
            int frequency;              //! Frequency
            bool fullscreen;            //! Fullscreen
        };
        
        
        /**
         * @brief Array of display modes.
         */
        typedef std::vector<DisplayMode> DisplayModeArray;
        
        
        /**
         * @brief Abstract canvas.
         */
        class EXENGAPI Screen : public Object {
        public:
            virtual ~Screen() {}
            
            /**
             * @brief enumDisplayModes
             * @return 
             */
            virtual DisplayModeArray enumDisplayModes() const = 0;
            
            /**
             * @brief enumDisplayModes
             */
            virtual void setDisplayMode(const DisplayMode &displayMode) = 0;
            
            /**
             * @brief Get the current display mode.
             */
            virtual DisplayMode  getDisplayMode() const = 0;
            
        };
    }
}

#endif // exeng_graphics_canvas_hpp
