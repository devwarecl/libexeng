/**
 * @file Screen.hpp
 * @brief Define the Screen abstract class, and the DisplayMode structucture.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_CANVAS_HPP__
#define __EXENG_GRAPHICS_CANVAS_HPP__

#include <vector>
#include <functional>

#include <exeng/Object.hpp>
#include <exeng/math/TSize.hpp>
#include <exeng/graphics/PixelFormat.hpp>

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
            
            exeng::math::Size2i size;   //! Width and height, in pixels.
            PixelFormat format;         //! Framebuffer format
            int frequency;              //! Frequency
            bool fullscreen;            //! Fullscreen
        };
        
        
        /**
         * @brief Array of display modes.
         */
        typedef std::vector<DisplayMode> DisplayModeArray;
        
        
        /**
         * @brief Abstract drawing canvas.
         */
        class EXENGAPI Screen : public Object {
        public:
            virtual ~Screen() {}
            
            /**
             * @brief Get the available displaymodes for the screen.
             */
            virtual DisplayModeArray enumDisplayModes() const = 0;
            
            /**
             * @brief enumDisplayModes
             */
            virtual void setDisplayMode(const DisplayMode &displayMode) = 0;
            
            /**
             * @brief Get the current display mode.
             */
            virtual DisplayMode getDisplayMode() const = 0;
            
            /**
             * @brief Raise events
             */
            virtual void pollEvents() = 0;
            
            /**
             * @brief Set the event handler for keyboard callbacks
             */
            virtual void setKeyboardCallback(const std::function<void()> &eventHandler) = 0;
            
            /**
             * @brief Get the current event handler for the key events
             */
            virtual std::function<void()> getKeyPressCallback() const = 0;
        };
    }
}

#endif // __EXENG_GRAPHICS_CANVAS_HPP__
