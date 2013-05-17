/**
 * @brief Define the Primitive enumeration.
 */

#ifndef exeng_graphics_primitivetype_hpp
#define exeng_graphics_primitivetype_hpp

#include "../TFlags.hpp"

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
            
            typedef TFlags<Enum> Flags;
        }
    }
}

#endif  //exeng_graphics_primitivetype_hpp
