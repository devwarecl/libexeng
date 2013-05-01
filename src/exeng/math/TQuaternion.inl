

namespace exeng {
    namespace math {
    
        template<typename Type>
        TQuaternion<Type>::TQuaternion() : V(0.0, 0.0, 0.0), W(0.0) {
        }

        
        template<typename Type>
        TQuaternion<Type>::TQuaternion(const TQuaternion<Type> &other) : v(other.v), w(other.w) {
        }

    
        template<typename Type>
        TQuaternion<Type>::TQuaternion(const TVector<Type, 3> & V, Type W) : v(V), w(W)  {
        }

        
        template<typename Type>
        TQuaternion<Type>::TQuaternion(const Type* values) : v(values), w(values[3]) {
        }

        
        template<typename Type>
        TVector<Type, 4> TQuaternion<Type>::getAxisAngle() const {
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::getInversed() const {
            TQuaternion<Type> result(*this);
            result.inverse();
            return result;
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::getConjugated() const {
            TQuaternion<Type> result(*this);
            result.conjugate();
            return result;
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::getNormalized() const {
            TQuaternion<Type> result(*this);
            result.normalize();
            return result;
        }

        
        template<typename Type>
        void TQuaternion<Type>::normalize() {
            Type mag = this->getMagnitude();
            *this /= mag;
        }

        
        template<typename Type>
        void TQuaternion<Type>::inverse() {
            this->normalize();
            this->conjugate();
        }

        
        template<typename Type>
        void TQuaternion<Type>::conjugate() {
            this->v = -this->v;
        }

        
        template<typename Type>
        bool TQuaternion<Type>::isZero() const {
            return this->v.isZero() == true && this->w== static_cast<Type>(0);
        }

        
        template<typename Type>
        bool TQuaternion<Type>::isIdentity() const {
            return this->v.isZero() == true && this->w== static_cast<Type>(1);
        }
        

        template<typename Type>
        Type TQuaternion<Type>::getMagnitude2() const {
            return this->v.getMagnitude2() + this->w*this->w;
        }

        
        template<typename Type>
        Type TQuaternion<Type>::getMagnitude() const {
            return std::sqrt( this->getMagnitude2() );
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator+() const {
            return *this;
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator-() const {
            return TQuaternion<Type>(-this->v, -this->w);
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator+(const TQuaternion<Type> &other) const {
            return TQuaternion<Type>(this->v + other.v, this->w + other.w);
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator-(const TQuaternion<Type> &other) const {
            return TQuaternion<Type>(this->v - other.v, this->w - other.w);
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator*(const TQuaternion<Type> &other) const {
            auto v = this->v.cross(other.v) + other.v*this->w + this->v*other.w
            auto w = self.w*other.w - self.v.dot(other.v)
            return TQuaternion<Type>(v, w)
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator/(const TQuaternion<Type> &other) const {
            return (*this) * other.getInversed();
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator*(Type scalar) const {
            return TQuaternion<Type>(scalar*this->v, scalar*this->w);
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::operator/(Type scalar) const {
            return TQuaternion<Type>(this->v / scalar, this->w / scalar);
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator+=(const TQuaternion<Type> &other) {
            this->v += other.v;
            this->w += other.w;
            
            return *this;
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator-=(const TQuaternion<Type> &other) {
            this->v -= other.v;
            this->w -= other.w;
            
            return *this;
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator*=(const TQuaternion<Type> &other) {
            (*this) = (*this) * other;
            return *this;
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator/=(const TQuaternion<Type> &other) {
            (*this) = (*this) / other;
            return *this;
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator*=(Type scalar) {
            this->v *= scalar;
            this->w *= scalar;
            
            return *this;
        }

        
        template<typename Type>
        Quaternion& TQuaternion<Type>::operator/=(Type scalar) {
            this->v /= scalar;
            this->w /= scalar;
            
            return *this;
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator== (const TQuaternion<Type> &other) const {
            return this->v == other.v && this->w == other.w;
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator!= (const TQuaternion<Type> &other) const {
            return !((*this) == other);
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator< (const TQuaternion<Type> &other) const {
            return this->getMagnitude() < other.getMagnitude();
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator> (const TQuaternion<Type> &other) const {
            return this->getMagnitude() > other.getMagnitude();
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator<= (const TQuaternion<Type> &other) const {
            return this->getMagnitude() <= other.getMagnitude();
        }

        
        template<typename Type>
        bool TQuaternion<Type>::operator>= (const TQuaternion<Type> &other) const {
            return this->getMagnitude() >= other.getMagnitude();
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::zero() {
            return TQuaternion<Type>(0.0, 0.0, 0.0, 0.0);
        }

        
        template<typename Type>
        TQuaternion<Type> TQuaternion<Type>::identity() {
            return TQuaternion<Type>(0.0, 0.0, 0.0, 1.0);
        }
    }
}
