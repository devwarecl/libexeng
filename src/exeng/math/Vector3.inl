
namespace exeng {
	namespace math {

		template<typename Type>
		Vector3<Type>::Vector3() {
			x = y = z = static_cast<Type>(0);
		}


		template<typename Type>
		Vector3<Type>::Vector3(Type x, Type y, Type z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}


		template<typename Type>
		Vector3<Type>::Vector3(Type value) {
			x = y = z = value;
		}


		template<typename Type>
		Vector3<Type>::Vector3(const Type *values) {
			this->x = values[0];
			this->y = values[1];
			this->z = values[2];
		}


		template<typename Type>
		Vector3<Type> Vector3<Type>::operator+ (const Vector3<Type> &other) const {

			Vector3<Type>

		}


		template<typename Type>
		Vector3<Type> Vector3<Type>::operator- (const Vector3<Type> &other) const {

		}


		template<typename Type>
		Vector3<Type> Vector3<Type>::operator* (Type scalar) const {

		}

		template<typename Type>
		Vector3<Type> Vector3<Type>::operator/ (Type scalar) const {

		}


		template<typename Type>
		Vector3<Type> Vector3<Type>::operator+ () const {

		}


		template<typename Type>
		Vector3<Type> Vector3<Type>::operator- () const {
		}


		template<typename Type>
		Vector3<Type>& Vector3<Type>::operator+= (const Vector3<Type> &other) {

		}


		template<typename Type>
		Vector3<Type>& Vector3<Type>::operator-= (const Vector3<Type> &other) {

		}


		template<typename Type>
		Vector3<Type>& Vector3<Type>::operator*= (Type scalar) {

		}


		template<typename Type>
		Vector3<Type>& Vector3<Type>::operator/= (Type scalar) {

		}


		template<typename Type>
		bool Vector3<Type>::operator== (const Vector3<Type> &other) const {

		}


		template<typename Type>
		bool Vector3<Type>::operator!= (const Vector3<Type> &other) const {

		}


		template<typename Type>
		Type& Vector3<Type>::operator[] (int index) {
			

		}

		template<typename Type>
		const Type& Vector3<Type>::operator[] (int index) const {

		}
	}
}
