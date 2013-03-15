
#include <cstring>

namespace exeng {
	namespace graphics {

		typedef exeng::math::Unroller< exeng::math::SequenceTypeTraits<Color> > ColorUnroller;

		Color::Color() {}

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

		inline Color Color::operator*( float scale ) const {
		}


		inline Color Color::operator/( float scale) const {
		}


		inline Color& Color::operator*=( float scale ) const {

		}


		inline Color& Color::operator/=( float scale) const {
		}


		inline float& Color::operator[] (int index) {

			this->data[index];
		}


		inline const float& Color::operator[] (int index) const {
			return this->data[index];
		}
	}
}
