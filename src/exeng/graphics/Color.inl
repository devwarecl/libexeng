
#include <cstring>
#include <iostream>

namespace exeng {
	namespace graphics {
        typedef exeng::math::SequenceTypeTraits<Color> ColorSequenceTraits;
		typedef exeng::math::Unroller<ColorSequenceTraits> ColorUnroller;

		inline Color::Color() {}

		inline Color::Color(float value) {
			this->red = this->green = this->blue = this->alpha = value;
		}


		inline Color::Color(const float *values) {
			std::memcpy(this->data, values, 4 * sizeof(float));
		}


		inline Color::Color(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) {
		}


		inline Color Color::operator+() const {
			return Color(*this);
		}

		
		inline Color Color::operator-() const {
            return *this;
		}


		inline Color Color::operator+(const Color &other) const {
			Color result;
			ColorUnroller::unroll<exeng::math::BinaryOperators::Add>(result, *this, other);
			return result;
		}


		inline Color Color::operator-(const Color &other) const {
			Color result;
			ColorUnroller::unroll<exeng::math::BinaryOperators::Sub>(result, *this, other);
			return result;
		}


		inline Color Color::operator*(const Color &other) const {
			Color result;
			ColorUnroller::unroll<exeng::math::BinaryOperators::Mul>(result, *this, other);
			return result;
		}


		inline Color Color::operator/(const Color &other) const {
			Color result;
			ColorUnroller::unroll<exeng::math::BinaryOperators::Div>(result, *this, other);
			return result;
		}


		inline Color& Color::operator+=(const Color &other) {
			ColorUnroller::unrollAssign<exeng::math::BinaryOperators::AddAssign>(*this, other);
			return *this;
		}


		inline Color& Color::operator-=(const Color &other) {
			ColorUnroller::unrollAssign<exeng::math::BinaryOperators::SubAssign>(*this, other);
			return *this;
		}


		inline Color& Color::operator*=(const Color &other) {
			ColorUnroller::unrollAssign<exeng::math::BinaryOperators::MulAssign>(*this, other);
			return *this;
		}


		inline Color& Color::operator/=(const Color &other) {
			ColorUnroller::unrollAssign<exeng::math::BinaryOperators::DivAssign>(*this, other);
			return *this;
		}

		
		inline Color Color::operator*( float scale ) {
            Color result;
            ColorUnroller::unrollScalar< exeng::math::BinaryOperators::Mul >(result, *this, scale);
            return result;
            
		}


		inline Color Color::operator/( float scale) {
            Color result;
            ColorUnroller::unrollScalar< exeng::math::BinaryOperators::Div >(result, *this, scale);
            return result;
		}


		inline Color& Color::operator*=( float scale ) {
            ColorUnroller::unrollScalar< exeng::math::BinaryOperators::Mul >(*this, *this, scale);
            return *this;
		}


		inline Color& Color::operator/=( float scale) {
            ColorUnroller::unrollScalar< exeng::math::BinaryOperators::Div >(*this, *this, scale);
            return *this;
		}


		inline float& Color::operator[] (int index) {
#ifdef EXENG_DEBUG
            if (index >= 4) {
                throw std::runtime_error("Index out of bounds");
            }
#endif
            return this->data[index];
		}


		inline const float& Color::operator[] (int index) const {
#ifdef EXENG_DEBUG
            if (index >= 4) {
                throw std::runtime_error("Index out of bounds");
            }
#endif
			return this->data[index];
		}
		
		
		inline Color::operator std::uint32_t() const {
            union {
                std::uint8_t values[4];
                std::uint32_t value;
            } convColor;
            
            // Convertir las componentes de cada color
            for (int i=0; i<4; ++i) {
                convColor.values[i] = static_cast<std::uint8_t>(this->data[i] * 255.0f);
            }
            
            return convColor.value;
        }
        
        
        inline void Color::set(float red, float green, float blue, float alpha) {
            this->red = red;
            this->green = green;
            this->blue = blue;
            this->alpha = alpha;
        }
	}
}
