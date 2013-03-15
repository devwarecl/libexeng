#ifndef __EXENG_GRAPHICS_COLOR_HPP__
#define __EXENG_GRAPHICS_COLOR_HPP__

#include <cstdint>
#include "../math/Operations.hpp"

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



namespace exeng {
	namespace graphics {

		/**
		 *	@brief Clase para almacenar numeros en punto flotante RGBA
		 */
		struct Color {
			Color();

			explicit Color(float value);
			explicit Color(const float *values);

			Color(float red, float green, float blue, float alpha=1.0f);

			Color operator+() const;
			Color operator-() const;
			Color operator+(const Color &other) const;
			Color operator-(const Color &other) const;
			Color operator*(const Color &other) const;
			Color operator/(const Color &other) const;

			Color& operator+=(const Color &other);
			Color& operator-=(const Color &other);
			Color& operator*=(const Color &other);
			Color& operator/=(const Color &other);

			Color operator*( float scale ) const;
			Color operator/( float scale) const;

			Color& operator*=( float scale ) const;
			Color& operator/=( float scale) const;

			float& operator[] (int index);

			const float& operator[] (int index) const;

			union {
				struct {
					float red, green, blue, alpha;
				};

				float data[4];
			};
		};
	}
}

// #include "Color.inl"

#endif	//__EXENG_GRAPHICS_COLOR_HPP__
