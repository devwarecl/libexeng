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


#include "PixelFormat.hpp"

#include <cassert>
#include <stdexcept>

/*
namespace exeng
{
    namespace graphics
    {
        int ColorFormat::getPitch(ColorFormat::Type pf)
        {
            switch (pf)
            {
            case ColorFormat::R8G8B8A8:
            case ColorFormat::R8G8B8X8:
            case ColorFormat::B8G8R8A8:
            case ColorFormat::B8G8R8X8:
                return 4;

            case ColorFormat::R8G8B8:
            case ColorFormat::B8G8R8:
                return 3;

            case ColorFormat::R5G5B5X1:
            case ColorFormat::R5G5B5A1:
            case ColorFormat::R5G6B5:
            case ColorFormat::L8A8:
                return 2;

            case ColorFormat::L8:
                return 1;

            default:
                throw std::invalid_argument("El argumento suministrado a ColorFormat::GetPith no es valido.");
            }
        }
    }
}
*/