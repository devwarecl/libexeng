/**
 * @file Vector.hpp
 * @brief Vector class and companion functions definition and implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_VECTOR_HPP__
#define __EXENG_VECTOR_HPP__

#include <iostream> //! TODO: Make it optional
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstring>

#include <xe/Common.hpp>
#include <xe/DataType.hpp>

#if defined(EXENG_DEBUG)
#include <stdexcept>
#endif

namespace xe { 
    template<typename Type, int size>
    struct VectorBase {
        Type data[size];
    };

	template<typename Type> 
    struct VectorBase<Type, 1> {
        union {
            Type data[1];
            struct { Type x; };
        };

		void set(Type x) {
            this->x = x;
        }

        void set(Type x, Type y) {
            this->set(x);
        }

		void set(Type x, Type y, Type z) {
             this->set(x);
        }

		 void set(Type x, Type y, Type z, Type w) {
            this->set(x);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 2> {
        union {
            Type data[2];
            struct { Type x, y; };
        };

        void set(Type x, Type y) {
            this->x = x;
            this->y = y;
        }

		void set(Type x, Type y, Type z) {
             this->set(x, y);
        }

		 void set(Type x, Type y, Type z, Type w) {
            this->set(x, y);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 3> {
        union {
            Type data[3];
            struct { Type x, y, z; };
        };

        void set(Type x, Type y, Type z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

		 void set(Type x, Type y, Type z, Type w) {
            this->set(x, y, z);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 4> {
        union {
            Type data[4];
            struct { Type x, y, z, w; };
        };

        void set(Type x, Type y, Type z, Type w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    /**
     * @brief Base vector class
     */
    template<typename Type, int Size>
    class Vector : public VectorBase<Type, Size> {
	public:
		typedef Type type;
		static const int size = Size;
		static const DataType::Enum dataType = DataTypeTraits<Type>::Enum;

    private:
        typedef Vector<Type, Size> VectorType;

    public:
        using VectorBase<Type, Size>::set;

		Vector() {}

		Vector( const Vector<Type, Size - 1> &v, Type value) {
			for (int i=0; i<Size-1; i++) {
				VectorBase<Type, Size>::data[i] = v[i];
			}

			VectorBase<Type, Size>::data[Size-1] = value;
		}

        explicit Vector(const Type *arrayValues) {
			this->set(arrayValues);
		}

        explicit Vector(Type value) {
			this->set(value);
		}

        Vector(Type x, Type y) {
			this->set(Type());

			this->x = x;
			this->y = y;
		}

        Vector(Type x, Type y, Type z) {
			this->set(Type());

			this->x = x;
			this->y = y;
			this->z = z;
		}

        Vector(Type x, Type y, Type z, Type w) {
			this->set(Type());

			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

        void set(const Type *values) {
#if defined(EXENG_DEBUG)
			if (values == nullptr) {
				throw std::runtime_error("Vector<Type, Size>::set: Input value is a null pointer.");
			}
#endif
			std::memcpy(this->data, values, sizeof(Type)*Size);
		}

        void set(Type Value) {
			for(int i=0; i<Size; ++i) {
				this->data[i] = Value;
			}	
		}

        Type* getPtr() {
			return this->data;
		}
		
        const Type* getPtr() const {
			return this->data;
		}
		
        Type& operator[] (int index) {
#if defined(EXENG_DEBUG)
			if (index < 0 || index >= Size) {
				throw std::runtime_error("Vector<Type, Size>::operator[]: Index out of bounds.");
			}
#endif
			return this->data[index];
		}

        const Type& operator[] (int index) const {
#if defined(EXENG_DEBUG)
			if (index < 0 || index >= Size) {
				throw std::runtime_error("Vector<Type, Size>::operator[]: Index out of bounds.");
			}
#endif
			return this->data[index];
		}

        Vector operator+ (const Vector &rhs) const {
			Vector<Type, Size> result;

			for(int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] + rhs.data[i];
			}
    
			return result;
		}

        Vector& operator+= (const Vector &rhs) {
			*this = *this + rhs;

			return *this;
		}

        Vector operator- (const Vector &rhs) const {
			Vector<Type, Size> result;

			for(int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] - rhs.data[i];
			}
    
			return result;
		}
		
        Vector& operator-= (const Vector &rhs) {
			*this = *this - rhs;

			return *this;
		}

        Vector operator* (Type rhs) const {
			Vector<Type, Size> result;

			for(int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] * rhs;
			}
    
			return result;
		}

        Vector& operator*= (Type rhs) {
			*this = *this * rhs;

			return *this;
		}

        template<typename OtherType>
        friend Vector<OtherType, Size> operator* (Type Number, const Vector& Other)  {
            return Other*Number;
        }
    
        Vector operator/ (Type rhs) const {
			Vector<Type, Size> result;

			for(int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] / rhs;
			}
    
			return result;
		}
    
        Vector& operator/= (Type rhs) {
			*this = *this / rhs;

			return *this;
		}

        Vector operator* (const Vector &rhs) const {
			Vector<Type, Size> result;

			for (int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] * rhs.data[i];
			}
    
			return result;
		}

        Vector& operator*= (const Vector &rhs) {
			*this = *this * rhs;

			return *this;
		}

        Vector operator/ (const Vector &rhs) const {
			Vector<Type, Size> result;

			for(int i=0; i<Size; ++i) {
				result.data[i] = this->data[i] / rhs.data[i];
			}
    
			return result;
		}

        Vector& operator/= (const Vector rhs) {
			*this = *this / rhs;

			return *this;
		}

        Vector operator- () const {
			return Type(-1)* (*this);
		}

        bool operator== (const Vector &Other) const {
			return arrayCompare<Type, Size>(this->data, Other.data);
		}

        bool operator!= (const Vector &Other) const {
			return !(*this == Other);
		}

        friend Vector<Type, Size> operator* (Type scalar, const Vector<Type, Size>& other)  {
            return other * scalar;
        }
        
        template<typename OtherType, int OtherSize>
        operator Vector<OtherType, OtherSize>() const  {
            Vector<OtherType, OtherSize> result(static_cast<OtherType>(0));
            int minSize = std::min(OtherSize, Size);
        
            for(int i=0; i<minSize; ++i) {
                result[i] = static_cast<OtherType>( this->data[i] );
            }
        
            return result;
        }
    
        bool isZero() const  {
			return *this == Vector<Type, Size>::zero();
		}
		
        static Vector zero() {
			return Vector<Type, Size>(Type());
		}

		friend std::ostream& operator<< (std::ostream &os, const Vector<Type, Size> &v)  {
		    for(int i=0; i<Size; ++i) {
				os << std::fixed << std::setprecision(2) << v[i];
        
				if (i+1 != Size) {
					os << ", ";
				}
			}
			
			return os;
		}
    };

	template<typename Type, int Size>
    Type dot(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2)  {
		Type result = static_cast<Type>(0);

		for(int i=0; i<Size; ++i) {
			result += v1[i]*v2[i];
		}
    
		return result;
	}

	template<typename Type, int Size>
    Vector<Type, Size> cross(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) {
		Vector<Type, Size> result = {
			v1.y*v2.z - v1.z*v2.y, 
			v1.z*v2.x - v1.x*v2.z, 
			v1.x*v2.y - v1.y*v2.x
		};

		return result;
	}

	template<typename Type, int Size>
    Type dot(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, const Vector<Type, Size> &v3)  {
		return dot(v1, cross(v2, v3));
	}

	template<typename Type, int Size>
    Vector<Type, Size> cross(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, const Vector<Type, Size> &v3) 
	{
		return cross(v1, cross(v2, v3));
	}
	
	template<typename Type, int Size>
    Type abs2(const Vector<Type, Size> &v) 
	{
		return dot(v, v);
	}
    
	template<typename Type, int Size>
    Type abs(const Vector<Type, Size> &v) 
	{
		return std::sqrt(abs2(v));
	}
	
	template<typename Type, int Size>
    Vector<Type, Size> normalize(const Vector<Type, Size> &v)
	{
		return v / abs(v);
	}
	
	template<typename Type, int Size>
    Vector<Type, Size> maximize(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
	{
		Vector<Type, Size> result;

		for (int i=0; i<Size; ++i) {
			result.data[i] = std::max(v1[i], v2[i]);
		}

		return result;
	}
	
	template<typename Type, int Size>
    Vector<Type, Size> minimize(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
	{
		Vector<Type, Size> result;

		for (int i=0; i<Size; ++i) {
			result.data[i] = std::min(v1[i], v2[i]);
		}

		return result;
	}
	
	template<typename Type, int Size>
    Type max(const Vector<Type, Size> &v) 
	{
		Type result = v[0];

		for (int i=1; i<Size; ++i) {
			result = std::max(result, v[i]);
		}

		return result;
	}
	
	template<typename Type, int Size>
    Type min(const Vector<Type, Size> &v) 
	{
		Type result = v[0];

		for (int i=1; i<Size; ++i) {
			result = std::min(result, v[i]);
		}

		return result;
	}

	template<typename Type, int Size>
    const Vector<Type, Size> proj(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
	{
		return v1 * ((dot(v1, v2)/abs2(v1, v1)));
		// return (this->dot(other) / this->getMagnitudeSq()) * (*this);
	}
	
	template<typename Type, int Size>
    Vector<Type, Size> lerp(const Vector<Type, Size>& v1, const Vector<Type, Size>& v2, Type t)
	{
		return t*v2 + v1*(Type(1) - t);
	}

    template<typename Type, typename Scalar>
    Type lerp(const Type &v1, const Type &v2, Scalar t) {
        return t*v2 + v1*(Scalar(1) - t);
    }

	template<typename Type, int Size>
    Vector<Type, Size> hermite (
		const Vector<Type, Size>& V1, const Vector<Type, Size>& T1, 
		const Vector<Type, Size>& V2, const Vector<Type, Size>& T2, 
		Type t)
	{
		Type ss = t*t;
		Type sss = ss*t;

		Type _2sss = sss+sss;
		Type _3ss = ss+ss+ss;
    
		return  V1*(_2sss - _3ss + Type(t))	+ 
				V2*(_3ss - _2sss) + 
				T1*(sss - (ss+ss) + t) + 
				T2*(sss - ss);
	}
	
	template<typename Type, int Size>
    bool equals(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, Type epsilon=Type()) 
	{
		for (int i=0; i<Size; ++i) {
			if ( std::abs( v1[i] - v2[i] ) > epsilon ) {
				return false;
			}
		}
		
		return true;
	}
    
    typedef Vector<float, 2> Vector2f;
    typedef Vector<float, 3> Vector3f;
    typedef Vector<float, 4> Vector4f;

    typedef Vector<double, 2> Vector2d;
    typedef Vector<double, 3> Vector3d;
    typedef Vector<double, 4> Vector4d;

    typedef Vector<int, 2> Vector2i;
    typedef Vector<int, 3> Vector3i;
    typedef Vector<int, 4> Vector4i;

	typedef Vector<unsigned char, 2> Vector2ub;
    typedef Vector<unsigned char, 3> Vector3ub;
    typedef Vector<unsigned char, 4> Vector4ub;
}

#endif	//__EXENG_VECTOR_HPP__
