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

#ifndef __EXENG_MATH_Vector_HPP__
#define __EXENG_MATH_Vector_HPP__

#include <iosfwd>
#include <algorithm>
#include "Common.hpp"

namespace exeng { 
    template<typename Type, int size>
    struct VectorBase {
        Type data[size];
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
    private:
        typedef Vector<Type, Size> VectorType;

    public:
        using VectorBase<Type, Size>::set;


        /**
         * @brief PENDIENTE
         */
        Vector();

        /**
         * @brief PENDIENTE
         */
        explicit Vector(const Type *Array);

        /**
         * @brief PENDIENTE
         */
        explicit Vector(Type Value);

        /**
         * @brief PENDIENTE
         */
        Vector(Type x, Type y);

        /**
         * @brief PENDIENTE
         */
        Vector(Type x, Type y, Type z);

        /**
         * @brief PENDIENTE
         */
        Vector(Type x, Type y, Type z, Type w);

        /**
         * @brief PENDIENTE
         */
        void set(const Type *Values);

        /**
         * @brief PENDIENTE
         */
        void set(Type Value);

        /**
         * @brief Devuelve la magnitud del vector elevada al cuadrado
         */
        Type getMagnitudeSq() const;

        /**
         * @brief Devuelve la magnitud del vector
         */
        Type getMagnitude() const;
    
        /**
         * @brief Normalize the vector.
         */
        void normalize();
    
        /**
         * @brief Establece la magnitud del vector
         */
        void setMagnitude(Type Magnitude);

        /**
         * @brief Get vector internal data pointer
         */
        Type* getPtr();

        /**
         * @brief Get vector internal data pointer
         */
        const Type* getPtr() const;
    
        /**
         * @brief Array like member access
         */
        Type& operator[] (int Index);

        /**
         * @brief Array like member access (const)
         */
        const Type& operator[] (int Index) const;

        /**
         * @brief Suma dos vectores
         */
        Vector operator+ (const Vector &Other) const;

        /**
         * @brief Suma dos vectores
         */
        Vector &operator+= (const Vector &Other);

        /**
         * @brief Resta dos vectores
         */
        Vector operator- (const Vector &Other) const;
    
        /**
         * @brief PENDIENTE
         */
        Vector &operator-= (const Vector &Other);

        /**
         * @brief Escala un vector
         */
        Vector operator* (Type Number) const;

        /**
         * @brief Escala un vector
         */
        template<typename OtherType>
        friend Vector<OtherType, Size> operator* (Type Number, const Vector& Other) {
            return Other*Number;
        }
    
        /**
         * @brief Escala un vector
         */
        Vector &operator*= (Type Number);

        /**
         * @brief Divide un vector por un numero
         */
        Vector operator/ (Type Number) const;
    
        /**
         * @brief Divide un vector por un numero
         */
        Vector &operator/= (Type Number);

        /**
         * @brief Escala un vector por otro vector
         */
        Vector operator* (const Vector &Other) const;

        /**
         * @brief Escala un vector por otro vector
         */
        Vector &operator*= (const Vector &Other);

        /**
         * @brief Divide un vector por otro vector
         */
        Vector operator/ (const Vector &Other) const;

        /**
         * @brief Divide un vector por otro vector
         */
        Vector &operator/= (const Vector &Other);

        /**
         * @brief Devuelve el vector negativo
         */
        Vector operator- () const;

        /**
         * @brief Operador de igualdad
         */
        bool operator == (const Vector &Other) const;

        /**
         * @brief Operador de desigualdad
         */
        bool operator != (const Vector &Other) const;

        /**
         * @brief Ve si un vector es mayor que otro vector
         */
        bool operator > (const Vector &Other) const;
    
        /**
         * @brief Ve si un vector es menor que otro vector
         */
        bool operator < (const Vector &Other) const;
    
        /**
         * @brief Ve si un vector es mayor o igual que otro vector
         */
        bool operator >= (const Vector &Other) const;
    
        /**
         * @brief Ve si un vector es menor o igual que otro vector
         */
        bool operator <= (const Vector &Other) const;


        /**
         * @brief PENDIENTE
         */
        friend Vector<Type, Size> operator* (Type scalar, const Vector<Type, Size>& other) {
            return other * scalar;
        }
        
        /**
         * @brief Convierte de un tipo de vector a otro
         */
        template<typename OtherType, int OtherSize>
        operator Vector<OtherType, OtherSize>() const {
            Vector<OtherType, OtherSize> result(static_cast<OtherType>(0));
            int minSize = std::min(OtherSize, Size);
        
            for(int i=0; i<minSize; ++i) {
                result[i] = static_cast<OtherType>( this->data[i] );
            }
        
            return result;
        }
    
    public:
    
        /**
         * @brief Calcula el producto punto entre dos vectores.
         * Este valor es representativo del coseno entre los dos vectores.
         */
        Type dot(const VectorType &other) const;

        /**
         * @brief Calcula el producto cruz entre dos vectores
         */
        VectorType cross(const VectorType &other) const;

    
        /**
         * @brief Calcula el triple producto escalar entre tres vectores
         */
        Type triple(const VectorType &other1, const VectorType &other2) const;
    
    
        /**
         * @brief Maximiza un vector
         */
        VectorType maximize(const VectorType &other) const;
    
        /**
         * @brief Minimiza un vector
         */
        VectorType minimize(const VectorType &other) const;
    
        /**
         * @brief Calcula la proyeccion vectorial del vector B sobre el vector A
         */
        VectorType proj(const VectorType &other) const;
    
        /**
         * @brief Calcula el componente escalar del vector B sobre el vector A
         */
        Type comp(const VectorType &other) const;

        /**
         * @brief Interpolacion lineal
         */
        static VectorType lerp(const VectorType& V1, const VectorType& V2, Type S);

        /**
         * @brief Interpolacion cubica
         */
        static VectorType hermite(const VectorType& V1, const VectorType& T1, const VectorType& V2, const VectorType& T2, Type S);
    
        /**
         * @brief Comprueba si dos vectores son iguales. Solo tiene sentido si el vector esta basado
         * en un tipo de datos de ṕunto flotante.
         */
        bool equals(VectorType &other, Type epsilon=Type()) const;
        
        /**
         * @brief Comprueba si el vector actual corresponde al vector zero.
         */
        bool isZero() const;
    
        /**
         * @brief Regresa el vector zero
         */
        static Vector zero();
    };

    typedef Vector<float, 2> Vector2f;
    typedef Vector<float, 3> Vector3f;
    typedef Vector<float, 4> Vector4f;

    typedef Vector<double, 2> Vector2d;
    typedef Vector<double, 3> Vector3d;
    typedef Vector<double, 4> Vector4d;

    typedef Vector<int, 2> Vector2i;
    typedef Vector<int, 3> Vector3i;
    typedef Vector<int, 4> Vector4i;
}

template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::Vector<Type, Size>& Vector);

#include "Vector.inl"

#endif	//__EXENG_MATH_Vector_HPP__
