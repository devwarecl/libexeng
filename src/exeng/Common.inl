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

namespace exeng { 
    //http://irshu.blogspot.com/2005/08/check-if-number-is-power-of-2-easier.html
    inline bool isPowerOf2(unsigned int x) {
        return ((x != 0) && !(x & (x - 1)));
    }

    template<typename T>
    const T Pi<T>::Value = static_cast<T>(3.14159265358979);

    template<typename T>
    const T Deg<T>::Value = static_cast<T>(180) / Pi<T>::Value;

    template<typename T>
    const T Rad<T>::Value = Pi<T>::Value / static_cast<T>(180);

    template<typename T>
    const T Epsilon<T>::Value = static_cast<T>(0.00001);

    template<typename T>
    inline T toDeg(T Rads) {
        return Rads * Deg<T>::Value;
    }

    template<typename T>
    inline T toRad(T Degs) {
        return Degs * Rad<T>::Value;
    }

    //Implementacion funcion Equals
    template<typename T>
    inline bool equals(T Val1, T Val2) {
        return Val1 == Val2;
    }

    template<typename Type>
    inline bool EqualsFloating(Type In1, Type In2) {
        return ::fabs(In1 - In2) < Epsilon<Type>::Value;
    }

    template<>
    inline bool equals<float>(float Val1, float Val2) {
        return EqualsFloating<float>(Val1, Val2);
    }

    template<>
    inline bool equals<double>(double Val1, double Val2) {
        return EqualsFloating<double>(Val1, Val2);
    }

    template<typename T, int Size>
    bool arrayCompare(const T* Arr1, const T* Arr2) {
        for(int i=0; i<Size; ++i)  {
            if (equals<T>(Arr1[i], Arr2[i]) == false) {
                return false;
            }
        }

        return true;
    }

    template<typename T, int Size>
    T arraySum(const T* Arr) {
        T Sum = static_cast<T>(0);

        for(int i=0; i<Size; ++i) {
            Sum += std::abs(Arr[i]);
        }

        return Sum;
    }

    //Implementacion de operaciones validas para todos los vectores
    template<typename Type, typename Scalar>
    inline Type hermite(const Type& V1, const Type& T1, const Type& V2, const Type& T2, Scalar s) {
        Scalar ss, sss, _2sss, _3ss;

        ss = s*s;
        sss = ss*s;

        _2sss = sss+sss;
        _3ss = ss+ss+ss;
    
        return  V1*(_2sss - _3ss + static_cast<Scalar>(s))+ 
                V2*(_3ss - _2sss)       + 
                T1*(sss - (ss+ss) + s)  + 
                T2*(sss - ss)           ;
    }

    template<typename Type, typename Scalar>
    inline Type lerp(const Type& V1, const Type& V2, Scalar S) {
        return S*V2 + V1*( static_cast<Scalar>(1) - S);
    }

    template<typename Type>
    inline Type proj(const Type &A, const Type &B) {
        return ( Type::Dot(A, B)/A.GetMagnitudeSq() )  *  A;
    }

    template<typename Type, typename Scalar>
    inline Scalar comp(const Type &A, const Type &B) {
        return Type::Dot(A, B)/A.GetMagnitude();
    }

    template<typename Type>
    inline void adjustValue(bool isLesser, Type& lesser, Type& greater, Type value) {
        //Izquierda
        if (isLesser == false) {
            if (greater < value) {
                greater = value; 
            }
            else {
                lesser = value;
            }
        } else {
            if (lesser > value) {
                lesser = value; 
            } else {
                greater = value;
            }
        }
    }

    // Implementacion para numeros en punto flotante
    template<typename Type> inline Type abs(Type value) {
        return std::fabs(value);
    }

    template<> inline long abs(long value) {
        return std::abs(value);
    }
}
