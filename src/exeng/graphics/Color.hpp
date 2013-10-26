/**
 * @file Color.hpp
 * @brief Color class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_COLOR_HPP__
#define __EXENG_GRAPHICS_COLOR_HPP__

#include <cstdint>
#include <stdexcept>
#include <exeng/math/Operations.hpp>

namespace exeng {
    namespace graphics {
        struct Color;
    }
}

namespace exeng {
    namespace math {
        template<>
        struct SequenceTypeTraits< exeng::graphics::Color > {
            typedef exeng::graphics::Color  SequenceType;
            typedef float                   SequenceValueType;
            static const int                Dimension=4;
        };
    }
}


namespace exeng { namespace graphics {

/**
    *	@brief Clase para almacenar numeros en punto flotante RGBA
    */
struct Color {
    Color();

    explicit Color(float value);
    explicit Color(const float *values);
    
    template<typename ArrayLikeType>
    explicit Color(const ArrayLikeType &other) {
        for (int i=0; i<4; ++i) {
            this->data[i] = static_cast<float>(other[i]);
        }
    }
    
    Color(float red, float green, float blue, float alpha=1.0f);
    
    void set(float red, float green, float blue, float alpha);
    
    Color operator+() const;
    Color operator-() const;
    Color operator+(const Color &other) const;
    Color operator-(const Color &other) const;
    Color operator*(const Color &other) const;
    Color operator/(const Color &other) const;
    Color operator*(float scale);
    Color operator/(float scale);

    Color& operator+=(const Color &other);
    Color& operator-=(const Color &other);
    Color& operator*=(const Color &other);
    Color& operator/=(const Color &other);
    Color& operator*=(float scale);
    Color& operator/=(float scale);

    float& operator[] (int index);

    const float& operator[] (int index) const;
    
    operator std::uint32_t() const;
    
    union {
        struct {
            float red, green, blue, alpha;
        };
        
        float data[4];
    };
};
        
}}

#include "Color.inl"

#endif	//__EXENG_GRAPHICS_COLOR_HPP__
