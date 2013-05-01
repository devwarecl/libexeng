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


#ifndef __EXENG_MATH_BASE_HPP__
#define __EXENG_MATH_BASE_HPP__

#include <cmath>

namespace exeng {
    namespace math {
        namespace Side2 {
            enum Type {
                Left, Bottom,
                Right, Top,
                Min = Left, Max = Top
            };
        }


        namespace Side3 {
            enum Type {
                Left, Bottom, Near, 
                Right, Top, Far,
                Min = Left, Max = Far
            };
        }


        namespace Edge2 {
            enum Type {
                LeftBottom, RightBottom,
                LeftTop, RightTop,
                Min = LeftBottom,
                Max = RightTop
            };
        }


        namespace Edge3 {
            enum Type {
                LeftBottomNear, RightBottomNear, 
                LeftTopNear, RightTopNear,
                LeftBottomFar, RightBottomFar, 
                LeftTopFar,	RightTopFar,
                Min = LeftBottomNear, Max = RightTopFar
            };
        }

        /**
         * @brief Comprueba si un numero es una potencia de dos.
         */
        bool isPowerOf2(unsigned int x);
        
        /**
         * @brief Define un valor de tolerancia para las operaciones en punto flotante
         */
        template<typename T>
        struct Epsilon { static const T Value; };

        /**
         * @brief Define el numero Pi
         */
        template<typename T>
        struct Pi  { static const T Value; };

        /**
         * @brief Define una constante para convertir de grados a radianes
         */
        template<typename T>
        struct Rad { static const T Value; };
        
        /**
         * @brief Define una constante para convertir de radianes a grados
         */
        template<typename T> struct Deg { static const T Value; }; 

        /**
         * @brief Convierte radianes a grados
         */
        template<typename T> 
        T toDeg(T Rads);

        /**
         * @brief Convierte de grados a radianes
         */
        template<typename T> 
        T toRad(T Degs);
        
        /**
         * @brief Compara dos valores del mismo tipo de datos
         */
        template<typename T> 
        bool equals(T Val1, T Val2);
        
        /**
         * @brief Compara dos arreglos estaticos.
         */
        template<typename T, int Size>
        bool arrayCompare(const T* Arr1, const T* Arr2);

        /**
         * @brief Calcula la suma acumulativa de los elementos de un arreglo.
         */
        template<typename T, int Size>
        T arraySum(const T* Arr);
        
        /**
         * @brief Calcula una interpolacion curva entre dos puntos.
         */
        template<typename Type, typename Scalar>
        Type hermite(const Type& V1, const Type& T1, const Type& V2, const Type& T2, Scalar s);
        
        /**
         * @brief Cacula la interpolacion lineal entre dos puntos.
         */
        template<typename Type, typename Scalar>
        Type lerp(const Type& V1, const Type& V2, Scalar S);

        /**
         * @brief Calcula la proyeccion de un vector sobre otro.
         */
        template<typename Type>
        Type proj(const Type &A, const Type &B);

        /**
         * @brief Calcula la magnitud de la proyeccion de un vector sobre otro.
         */
        template<typename Type, typename Scalar>
        Scalar comp(const Type &A, const Type &B);

        /**
         * @brief PENDIENTE
         */
        template<typename Type>
        void adjustValue(bool isLesser, Type& lesser, Type& greater, Type value);

		/**
		 * @brief Devuelve el valor absoluto del numero indicado
		 */
		template<typename Type>
		Type abs(Type value);

		double cos(double radians);
		float cos(float radians);

		double sin(double radians);
		float sin(float radians);
	}
}

#include "Common.inl"

#endif  //__MATH3D_BASE_HPP__
