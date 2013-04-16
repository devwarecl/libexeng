/**
 * @brief Implementa la interfaz de la plantilla exeng::math::TVector
 * @todo Optimize critical methods
 */

#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

namespace exeng {
    namespace math {
        template<typename Type, int Size>
        TVector<Type, Size>::TVector() { }


        template<typename Type, int Size>
        TVector<Type, Size>::TVector(const Type *values) {
            this->set(values);
        }

        
        template<typename Type, int Size>
        TVector<Type, Size>::TVector(Type value) {
            this->set(value);
        }


        template<typename Type, int Size>
        TVector<Type, Size>::TVector(Type x, Type y) {
			this->set(Type());

			this->x = x;
			this->y = y;
        }


        template<typename Type, int Size>
        TVector<Type, Size>::TVector(Type x, Type y, Type z) {
            this->set(Type());

			this->x = x;
			this->y = y;
			this->z = z;
        }

        
        template<typename Type, int Size>
        TVector<Type, Size>::TVector(Type x, Type y, Type z, Type w) {
            this->set(Type());

			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
        }


        template<typename Type, int Size>
        void TVector<Type, Size>::set(const Type *values) {
            assert(values != NULL);
            ::memcpy(this->data, values, sizeof(Type)*Size);
        }


        template<typename Type, int Size>
        void TVector<Type, Size>::set(Type Value) {
			for(int i=0; i<Size; ++i) {
                this->data[i] = Value;
			}
        }


        //Devuelve la magnitud del TVector<Type, Size> elevada al cuadrado
        template<typename Type, int Size>
        Type TVector<Type, Size>::getMagnitudeSq() const {
			Type result = this->dot(*this);

			return std::fabs(result);
        }


        //Devuelve la magnitud del TVector<Type, Size>
        template<typename Type, int Size>
        Type TVector<Type, Size>::getMagnitude() const {
            double Result;

            Result = static_cast<double>(this->getMagnitudeSq());
            Result = ::sqrt(Result);

            return static_cast<Type>(Result);
        }

        
        template<typename Type, int Size>
        void TVector<Type, Size>::normalize() {
            this->setMagnitude(static_cast<Type>(1));
        }
            

        //Establece la magnitud del TVector<Type, Size>
        template<typename Type, int Size>
        void TVector<Type, Size>::setMagnitude(Type Magnitude) {
            Type Scale;

            Scale = Magnitude/this->getMagnitude();

            *this *= Scale;
        }


        //!Get TVector<Type, Size> internal data pointer
        template<typename Type, int Size>
        Type* TVector<Type, Size>::getPtr() {
            return this->data;
        }


        //!Get TVector<Type, Size> internal data pointer
        template<typename Type, int Size>
        const Type* TVector<Type, Size>::getPtr() const {
            return this->data;
        }


        template<typename Type, int Size>
        Type& TVector<Type, Size>::operator[] (int Index) {
            assert(Index < Size);
            return this->data[Index];
        }


        template<typename Type, int Size>
        const Type& TVector<Type, Size>::operator[] (int Index) const {
            assert(Index < Size);
            return this->data[Index];
        }


        //Suma dos vectores
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator+ (const TVector<Type, Size> &Other) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] + Other.data[i];
			}
            
            return Result;
        }


        //Suma dos vectores
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator+= (const TVector<Type, Size> &Other) {
            for(int i=0; i<Size; ++i) {
                this->data[i] += Other.data[i];
			}

            return *this;
        }


        //Resta dos vectores
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator- (const TVector<Type, Size> &Other) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] - Other.data[i];
			}
            
            return Result;
        }


        //Resta dos vectores
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator-= (const TVector<Type, Size> &Other) {
            for(int i=0; i<Size; ++i) {
                this->data[i] -= Other.data[i];
			}

            return *this;
        }


        // Escala un TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator* (Type Number) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] * Number;
			}
            
            return Result;
        }


        //Escala un TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator*= (Type Number) {
            for(int i=0; i<Size; ++i) {
                this->data[i] *= Number;
			}
            
            return *this;
        }
            

        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator/ (Type Number) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] / Number;
			}
            
            return Result;
        }


        //Divide un TVector<Type, Size> por un numero
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator/= (Type Number) {
            for(int i=0; i<Size; ++i) {
                this->data[i] /= Number;
			}

            return *this;
        }


        //Escala un TVector<Type, Size> por otro TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator* (const TVector<Type, Size> &Other) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] * Other.data[i];
			}
            
            return Result;
        }


        //Escala un TVector<Type, Size> por otro TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator*= (const TVector<Type, Size> &Other) {
            for(int i=0; i<Size; ++i) {
                this->data[i] *= Other.data[i];
			}

            return *this;
        }

        //Divide un TVector<Type, Size> por otro TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator/ (const TVector<Type, Size> &Other) const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = this->data[i] / Other.data[i];
			}
            
            return Result;
        }

        //Divide un TVector<Type, Size> por otro TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size>& TVector<Type, Size>::operator/= (const TVector<Type, Size> &Other) {
            for(int i=0; i<Size; ++i) {
                this->data[i] /= Other.data[i];
			}
            
            return *this;
        }


        //Devuelve el TVector<Type, Size> negativo
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::operator- () const {
            TVector<Type, Size> Result;

            for(int i=0; i<Size; ++i) {
                Result.data[i] = -this->data[i];
			}
            
            return Result;
        }


        //Operador de igualdad
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator== (const TVector<Type, Size> &Other) const {
            return arrayCompare<Type, Size>(this->data, Other.data);
        }


        //Operador de desigualdad
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator!= (const TVector<Type, Size> &Other) const {
            return !(*this == Other);
        }


        //Ve si un TVector<Type, Size> es mayor que otro TVector<Type, Size>
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator> (const TVector<Type, Size> &Other) const {
            return arraySum<Type, Size>(this->data) > arraySum<Type, Size>(Other.data);
        }


        //Ve si un TVector<Type, Size> es menor que otro TVector<Type, Size>
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator< (const TVector<Type, Size> &Other) const {
            return !(*this > Other);
        }

        //Ve si un TVector<Type, Size> es mayor o igual que otro TVector<Type, Size>
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator>= (const TVector<Type, Size> &Other) const {
            return (*this == Other) || (*this > Other);
        }

        //Ve si un TVector<Type, Size> es menor o igual que otro TVector<Type, Size>
        template<typename Type, int Size>
        bool TVector<Type, Size>::operator<= (const TVector<Type, Size> &Other) const {
            return (*this == Other) || (*this < Other);
        }


        //Calcula el producto punto entre dos vectores.
        //Este valor es representativo del coseno entre los dos vectores.
        template<typename Type, int Size>
        Type TVector<Type, Size>::dot(const TVector<Type, Size> &other) const {
            Type result = static_cast<Type>(0);

            for(int i=0; i<Size; ++i)  {
                result += this->data[i]*other.data[i];
			}
            
            return result;
        }


        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::cross(const TVector<Type, Size> &other) const {	    
            TVector<Type, Size> result;

            result.x = this->y*other.z - this->z*other.y;
            result.y = this->z*other.x - this->x*other.z;
            result.z = this->x*other.y - this->y*other.x;

            return result;
        }


        //Maximiza un TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::maximize(const TVector<Type, Size> &other) const {
            TVector<Type, Size> result;

            for (int i=0; i<Size; ++i) {
                result.data[i] = std::max(this->data[i], other.data[i]);
			}

            return result;
        }


        //Minimiza un TVector<Type, Size>
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::minimize(const TVector<Type, Size> &other) const {
            TVector<Type, Size> result;

            for (int i=0; i<Size; ++i) {
                result.data[i] = std::min(this->data[i], other.data[i]);
			}

            return result;
        }


        template<typename Type, int Size>
        TVector<Type, Size> lerp(const TVector<Type, Size>& V1, const TVector<Type, Size>& V2, Type S) {
            return S*V2 + V1*( static_cast<Type>(1) - S);
        }


        //Interpolacion cubica
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::hermite(const TVector<Type, Size>& V1, const TVector<Type, Size>& T1, const TVector<Type, Size>& V2, const TVector<Type, Size>& T2, Type s) {
            Type ss, sss, _2sss, _3ss;

            ss = s*s;
            sss = ss*s;

            _2sss = sss+sss;
            _3ss = ss+ss+ss;
            
            return  V1*(_2sss - _3ss + static_cast<Type>(s))	+ 
                    V2*(_3ss - _2sss)							+ 
                    T1*(sss - (ss+ss) + s)						+ 
                    T2*(sss - ss);
        }


        //Calcula la proyeccion vectorial del TVector<Type, Size> B sobre el TVector<Type, Size> A
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::proj(const TVector<Type, Size> &other) const {
			return (this->dot(other) / this->getMagnitudeSq()) * (*this);
        }


        //Calcula el componente escalar del TVector<Type, Size> B sobre el TVector<Type, Size> A
        template<typename Type, int Size>
        Type TVector<Type, Size>::comp(const TVector<Type, Size> &other) const {
			return this->dot(other) / this->getMagnitude();
        }
        
        
        template<typename Type, int Size>
        bool TVector<Type, Size>::equals(TVector<Type, Size> &other, Type epsilon) const {
            for (int i=0; i<Size; ++i) {
                if ( exeng::math::abs( this->data[i] - other.data[i] ) > epsilon ) {
                    return false;
                }
            }
            
            return true;
        }
        
        
        template<typename Type, int Size>
        bool TVector<Type, Size>::isZero() const {
            return *this == TVector<Type, Size>::zero();
        }
        
        
        template<typename Type, int Size>
        TVector<Type, Size> TVector<Type, Size>::zero() {
            return TVector<Type, Size>(Type());
        }
    }
}


template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::math::TVector<Type, Size>& Vector) {
    os << "(";
    
    for(int i=0; i<Size; ++i) {
        os << std::fixed << std::setprecision( 4 ) << Vector[i];
        
        if (i + 1 != Size) {
            os << ", ";
        }
    }
    
    os << ")";
    
    return os;
}