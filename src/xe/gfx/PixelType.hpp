

#ifndef __EXENG_GRAPHICS_PIXELTYPE_HPP__
#define __EXENG_GRAPHICS_PIXELTYPE_HPP__

namespace xe  {
    namespace gfx {
        /**
         * @brief El tipo de datos utilizado para almacenar un pixel.
         * @TODO Evaluar mejor el proposito de esta enumeracion
         */
        enum class PixelType {
            Unknown,
            Integer,
            Float
        };
    }
}

#endif  //__EXENG_GRAPHICS_PIXELTYPE_HPP__
