/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 - 2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_MATH_BASE_HPP__
#define __EXENG_MATH_BASE_HPP__

#include <cmath>
#include <exeng/Enum.hpp>

namespace exeng { 
    struct Side2 : public Enum {
        enum Type {
            Left, Bottom,
            Right, Top,
            Min = Left, Max = Top
        };
    };

    struct Side3 : public Enum {
        enum Type {
            Left, Bottom, Near, 
            Right, Top, Far,
            Min = Left, Max = Far
        };
    };

    struct Edge2 : public Enum {
        enum Type {
            LeftBottom, RightBottom,
            LeftTop, RightTop,
            Min = LeftBottom,
            Max = RightTop
        };
    };

    struct Edge3 : public Enum {
        enum Type {
            LeftBottomNear, RightBottomNear, 
            LeftTopNear, RightTopNear,
            LeftBottomFar, RightBottomFar, 
            LeftTopFar,	RightTopFar,
            Min = LeftBottomNear, Max = RightTopFar
        };
    };

    bool isPowerOf2(unsigned int x);

    template<typename T>
    struct Epsilon { static const T Value; };

    template<typename T>
    struct Pi  { static const T Value; };

    template<typename T>
    struct Rad { static const T Value; };

    template<typename T> struct Deg { static const T Value; }; 
    
    template<typename T> 
    T toDeg(T Rads);

    template<typename T> 
    T toRad(T Degs);

    template<typename T> 
    bool equals(T Val1, T Val2);

    template<typename T, int Size>
    bool arrayCompare(const T* Arr1, const T* Arr2);

    template<typename T, int Size>
    T arraySum(const T* Arr);

    template<typename Type, typename Scalar>
    Type hermite(const Type& V1, const Type& T1, const Type& V2, const Type& T2, Scalar s);

    template<typename Type, typename Scalar>
    Type lerp(const Type& V1, const Type& V2, Scalar S);

    template<typename Type>
    Type proj(const Type &A, const Type &B);

    template<typename Type, typename Scalar>
    Scalar comp(const Type &A, const Type &B);

    template<typename Type>
    void adjustValue(bool isLesser, Type& lesser, Type& greater, Type value);

    template<typename Type>
    Type abs(Type value);

    double cos(double radians);
    float cos(float radians);

    double sin(double radians);
    float sin(float radians);
}

#include "Common.inl"

#endif  //__EXENG_MATH_BASE_HPP__
