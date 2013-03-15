
#include "TVector.hpp"

namespace exeng {
	namespace math {
		template<typename Type>
		struct Vector3 {

			Vector3();

			Vector3(Type x, Type y, Type z);

			explicit Vector3(Type value);
			explicit Vector3(const Type *values);

			Vector3<Type> operator+ (const Vector3<Type> &other) const;
			Vector3<Type> operator- (const Vector3<Type> &other) const;
			Vector3<Type> operator* (Type scalar) const;
			Vector3<Type> operator/ (Type scalar) const;

			Vector3<Type> operator+ () const;
			Vector3<Type> operator- () const;

			Vector3<Type>& operator+= (const Vector3<Type> &other);
			Vector3<Type>& operator-= (const Vector3<Type> &other);
			Vector3<Type>& operator*= (Type scalar);
			Vector3<Type>& operator/= (Type scalar);

			bool operator== (const Vector3<Type> &other) const;
			bool operator!= (const Vector3<Type> &other) const;

			Type& operator[] (int index);

			const Type& operator[] (int index) const;


			template<typename Type>
			friend Vector3<Type> operator* (Type scalar, const Vector3<Type> &other) {
				return other * scalar;
			}

			template<typename Type>
			friend Vector3<Type> operator/ (Type scalar, const Vector3<Type> &other) {
				return other / scalar;
			}


			template<typename OtherType> 
			operator Vector3<OtherType>() const {
				return Vector3<OtherType>(x, y, z);
			}

			union {
				struct {
					Type x, y, z;
				};

				TVector<Type, 3> data;
			};
		};
	}
}

#include "Vector3.inl"
