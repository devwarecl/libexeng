

#ifndef __EXENG_GRAPHICS_PIXELTYPE_HPP__
#define __EXENG_GRAPHICS_PIXELTYPE_HPP__

namespace exeng
{
    namespace graphics
    {
        /**
         * @brief El tipo de datos utilizado para almacenar un pixel.
         * @TODO Evaluar mejor el proposito de esta enumeracion
         */
        namespace PixelType
        {
            enum Type
            {
                Unknown,
                Integer,
                Float
            };
        }
    }
}

#endif  //__EXENG_GRAPHICS_PIXELTYPE_HPP__
