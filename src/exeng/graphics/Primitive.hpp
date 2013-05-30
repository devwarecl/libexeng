/**
 * @file Primitive.hpp
 * @brief Primitive::Enum enumeration
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_PRIMITIVE_HPP__
#define __EXENG_GRAPHICS_PRIMITIVE_HPP__

#include <exeng/TFlags.hpp>

namespace exeng {
    namespace graphics {
        /**
         * @brief Fundamental rendering primitives
         */
        namespace Primitive {
            enum Enum {
                PointList       = 0x00001001,   //! Point lists
                
                LineList        = 0x00002001,   //! Line lists.
                LineStrip       = 0x00002002,   //! Line strip.
                LineLoop        = 0x00002003,   //! Line loop
                
                TriangleList    = 0x00004001,   //! Triangle lists
                TriangleStrip   = 0x00004002,   //! Triangle strips
                TriangleFan     = 0x00004003,   //! Triangle fans
                
                // Group markers. Used for check if a given primitive 
                // is a point, line or triangle. They are not valid
                // enumeration entries.
                Point           = 0x00001000,
                Line            = 0x00002000,
                Triangle        = 0x00004000
            };
            
            inline bool isTriangle(Enum e) {
                return e & Triangle;
            }
            
            inline bool isLine(Enum e) {
                return e & Line;
            }
            
            inline bool isPoint(Enum e) {
                return e & Point;
            }
        }
    }
}

#endif  //exeng_graphics_primitivetype_hpp
