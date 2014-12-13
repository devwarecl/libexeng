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

#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

namespace exeng { 

    template<typename Type, int Size>
    Vector<Type, Size>::Vector() { }


    template<typename Type, int Size>
    Vector<Type, Size>::Vector(const Type *values) {
        this->set(values);
    }


    template<typename Type, int Size>
    Vector<Type, Size>::Vector(Type value) {
        this->set(value);
    }


    template<typename Type, int Size>
    Vector<Type, Size>::Vector(Type x, Type y) {
        this->set(Type());

        this->x = x;
        this->y = y;
    }


    template<typename Type, int Size>
    Vector<Type, Size>::Vector(Type x, Type y, Type z) {
        this->set(Type());

        this->x = x;
        this->y = y;
        this->z = z;
    }


    template<typename Type, int Size>
    Vector<Type, Size>::Vector(Type x, Type y, Type z, Type w) {
        this->set(Type());

        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }


    template<typename Type, int Size>
    void Vector<Type, Size>::set(const Type *values) {
        assert(values != NULL);
        ::memcpy(this->data, values, sizeof(Type)*Size);
    }


    template<typename Type, int Size>
    void Vector<Type, Size>::set(Type Value) {
        for(int i=0; i<Size; ++i) {
            this->data[i] = Value;
        }
    }


    //Devuelve la magnitud del Vector<Type, Size> elevada al cuadrado
    template<typename Type, int Size>
    Type Vector<Type, Size>::getMagnitudeSq() const {
        Type result = this->dot(*this);

        return std::fabs(result);
    }


    //Devuelve la magnitud del Vector<Type, Size>
    template<typename Type, int Size>
    Type Vector<Type, Size>::getMagnitude() const {
        double Result;

        Result = static_cast<double>(this->getMagnitudeSq());
        Result = ::sqrt(Result);

        return static_cast<Type>(Result);
    }


    template<typename Type, int Size>
    void Vector<Type, Size>::normalize() {
        this->setMagnitude(static_cast<Type>(1));
    }
    

    //Establece la magnitud del Vector<Type, Size>
    template<typename Type, int Size>
    void Vector<Type, Size>::setMagnitude(Type Magnitude) {
        Type Scale;

        Scale = Magnitude/this->getMagnitude();

        *this *= Scale;
    }


    //!Get Vector<Type, Size> internal data pointer
    template<typename Type, int Size>
    Type* Vector<Type, Size>::getPtr() {
        return this->data;
    }


    //!Get Vector<Type, Size> internal data pointer
    template<typename Type, int Size>
    const Type* Vector<Type, Size>::getPtr() const {
        return this->data;
    }


    template<typename Type, int Size>
    Type& Vector<Type, Size>::operator[] (int Index) {
        assert(Index < Size);
        return this->data[Index];
    }


    template<typename Type, int Size>
    const Type& Vector<Type, Size>::operator[] (int Index) const {
        assert(Index < Size);
        return this->data[Index];
    }


    //Suma dos vectores
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator+ (const Vector<Type, Size> &Other) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] + Other.data[i];
        }
    
        return Result;
    }


    //Suma dos vectores
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator+= (const Vector<Type, Size> &Other) {
        for(int i=0; i<Size; ++i) {
            this->data[i] += Other.data[i];
        }

        return *this;
    }


    //Resta dos vectores
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator- (const Vector<Type, Size> &Other) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] - Other.data[i];
        }
    
        return Result;
    }


    //Resta dos vectores
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator-= (const Vector<Type, Size> &Other) {
        for(int i=0; i<Size; ++i) {
            this->data[i] -= Other.data[i];
        }

        return *this;
    }


    // Escala un Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator* (Type Number) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] * Number;
        }
    
        return Result;
    }


    //Escala un Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator*= (Type Number) {
        for(int i=0; i<Size; ++i) {
            this->data[i] *= Number;
        }
    
        return *this;
    }
    

    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator/ (Type Number) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] / Number;
        }
    
        return Result;
    }


    //Divide un Vector<Type, Size> por un numero
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator/= (Type Number) {
        for(int i=0; i<Size; ++i) {
            this->data[i] /= Number;
        }

        return *this;
    }


    //Escala un Vector<Type, Size> por otro Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator* (const Vector<Type, Size> &Other) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] * Other.data[i];
        }
    
        return Result;
    }


    //Escala un Vector<Type, Size> por otro Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator*= (const Vector<Type, Size> &Other) {
        for(int i=0; i<Size; ++i) {
            this->data[i] *= Other.data[i];
        }

        return *this;
    }

    //Divide un Vector<Type, Size> por otro Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator/ (const Vector<Type, Size> &Other) const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = this->data[i] / Other.data[i];
        }
    
        return Result;
    }

    //Divide un Vector<Type, Size> por otro Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size>& Vector<Type, Size>::operator/= (const Vector<Type, Size> &Other) {
        for(int i=0; i<Size; ++i) {
            this->data[i] /= Other.data[i];
        }
    
        return *this;
    }


    //Devuelve el Vector<Type, Size> negativo
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::operator- () const {
        Vector<Type, Size> Result;

        for(int i=0; i<Size; ++i) {
            Result.data[i] = -this->data[i];
        }
    
        return Result;
    }


    //Operador de igualdad
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator== (const Vector<Type, Size> &Other) const {
        return arrayCompare<Type, Size>(this->data, Other.data);
    }


    //Operador de desigualdad
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator!= (const Vector<Type, Size> &Other) const {
        return !(*this == Other);
    }


    //Ve si un Vector<Type, Size> es mayor que otro Vector<Type, Size>
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator> (const Vector<Type, Size> &Other) const {
        return arraySum<Type, Size>(this->data) > arraySum<Type, Size>(Other.data);
    }


    //Ve si un Vector<Type, Size> es menor que otro Vector<Type, Size>
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator< (const Vector<Type, Size> &Other) const {
        return !(*this > Other);
    }

    //Ve si un Vector<Type, Size> es mayor o igual que otro Vector<Type, Size>
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator>= (const Vector<Type, Size> &Other) const {
        return (*this == Other) || (*this > Other);
    }

    //Ve si un Vector<Type, Size> es menor o igual que otro Vector<Type, Size>
    template<typename Type, int Size>
    bool Vector<Type, Size>::operator<= (const Vector<Type, Size> &Other) const {
        return (*this == Other) || (*this < Other);
    }


    //Calcula el producto punto entre dos vectores.
    //Este valor es representativo del coseno entre los dos vectores.
    template<typename Type, int Size>
    Type Vector<Type, Size>::dot(const Vector<Type, Size> &other) const {
        Type result = static_cast<Type>(0);

        for(int i=0; i<Size; ++i)  {
            result += this->data[i]*other.data[i];
        }
    
        return result;
    }


    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::cross(const Vector<Type, Size> &other) const {	    
        Vector<Type, Size> result;

        result.x = this->y*other.z - this->z*other.y;
        result.y = this->z*other.x - this->x*other.z;
        result.z = this->x*other.y - this->y*other.x;

        return result;
    }


    template<typename Type, int Size>
    Type Vector<Type, Size>::triple(const Vector<Type, Size> &other1, const Vector<Type, Size> &other2) const {
        return this->cross(other1).dot(other2);
    }

    //Maximiza un Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::maximize(const Vector<Type, Size> &other) const {
        Vector<Type, Size> result;

        for (int i=0; i<Size; ++i) {
            result.data[i] = std::max(this->data[i], other.data[i]);
        }

        return result;
    }


    //Minimiza un Vector<Type, Size>
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::minimize(const Vector<Type, Size> &other) const {
        Vector<Type, Size> result;

        for (int i=0; i<Size; ++i) {
            result.data[i] = std::min(this->data[i], other.data[i]);
        }

        return result;
    }


    template<typename Type, int Size>
    Vector<Type, Size> lerp(const Vector<Type, Size>& V1, const Vector<Type, Size>& V2, Type S) {
        return S*V2 + V1*( static_cast<Type>(1) - S);
    }


    //Interpolacion cubica
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::hermite(const Vector<Type, Size>& V1, const Vector<Type, Size>& T1, const Vector<Type, Size>& V2, const Vector<Type, Size>& T2, Type s) {
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


    //Calcula la proyeccion vectorial del Vector<Type, Size> B sobre el Vector<Type, Size> A
    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::proj(const Vector<Type, Size> &other) const {
        return (this->dot(other) / this->getMagnitudeSq()) * (*this);
    }


    //Calcula el componente escalar del Vector<Type, Size> B sobre el Vector<Type, Size> A
    template<typename Type, int Size>
    Type Vector<Type, Size>::comp(const Vector<Type, Size> &other) const {
        return this->dot(other) / this->getMagnitude();
    }


    template<typename Type, int Size>
    bool Vector<Type, Size>::equals(Vector<Type, Size> &other, Type epsilon) const {
        for (int i=0; i<Size; ++i) {
            if ( exeng::abs( this->data[i] - other.data[i] ) > epsilon ) {
                return false;
            }
        }
    
        return true;
    }


    template<typename Type, int Size>
    bool Vector<Type, Size>::isZero() const {
        return *this == Vector<Type, Size>::zero();
    }


    template<typename Type, int Size>
    Vector<Type, Size> Vector<Type, Size>::zero() {
        return Vector<Type, Size>(Type());
    }
}


