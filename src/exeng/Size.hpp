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


#ifndef __EXENG_MATH_Size_HPP__
#define __EXENG_MATH_Size_HPP__

#include "Vector.hpp"
#include <iosfwd>

namespace exeng {
    template<typename Type, int Dimension>  class SizeBase;

    template<typename Type> class SizeBase<Type, 2> {
    public:
        union {
            struct { Type width, height; };
            Type data[2];
        };
    
    public:
        SizeBase() {}

        SizeBase(Type width, Type height) {
            this->set(width, height);
        }

        void set(Type width, Type height) {
            this->width = width;
            this->height = height;
        }
    };


    template<typename Type> class SizeBase<Type, 3> {
    public:
        union {
            struct { Type width, height, depth; };
            Type data[3];
        };

    public:
        SizeBase() {}

        SizeBase(Type width, Type height, Type depth) {
            this->set(width, height, depth);
        }

        void set(Type width, Type height, Type depth) {
            this->width = width;
            this->height = height;
            this->depth = depth;
        }
    };


    /**
     * @brief Documentacion pendiente.
     */
    template<typename Type, int Dimension>
    class Size : public SizeBase<Type, Dimension> {
    public:
        typedef Size<Type, Dimension> SizeType;
        typedef Vector<Type, Dimension> VectorType;
    
    public:
        using SizeBase<Type, Dimension>::set;

        /**
         * @brief Documentacion pendiente.
         */
        Size();
    
        /**
         * @brief Documentacion pendiente.
         */
        explicit Size(Type baseSize);
    
        /**
         * @brief Documentacion pendiente.
         */
        explicit Size(const Type* arrIn);
    
        /**
         * @brief Documentacion pendiente.
         */
        explicit Size(const VectorType &inVect);
    
        /**
         * @brief Documentacion pendiente.
         */
        Size(Type Width, Type Height);
    
        /**
         * @brief Documentacion pendiente.
         */
        Size(Type Width, Type Height, Type Depth);
    
        /**
         * @brief Documentacion pendiente.
         */
        void set(Type baseSize);
    
        /**
         * @brief Documentacion pendiente.
         */
        void set(const Type* arrIn);
    
        /**
         * @brief Documentacion pendiente.
         */
        void set(const VectorType &inVect);
    

        /**
         * @brief Documentacion pendiente.
         */
        bool operator!= (const SizeType& rhs) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        bool operator== (const SizeType& rhs) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        bool operator> (const SizeType& rhs) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        bool operator< (const SizeType& rhs) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        bool operator>= (const SizeType& rhs) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        bool operator<= (const SizeType& rhs) const;
        
        /**
         * @brief Devuelve o establece el elemento que se encuentre en la posicion indicada
         */
        Type& operator[] (int index);
        
        /**
         * @brief Devuelve o establece el elemento que se encuentre en la posicion indicada
         */
        const Type& operator[] (int index) const;
        
        /**
         * @brief Documentacion pendiente.
         */
        operator Vector<Type, Dimension>() const;
        
        /**
         * @brief Documentacion pendiente.
         */
        Type* getPtr();
        
        /**
         * @brief Documentacion pendiente.
         */
        const Type* getPtr() const;
        
        /**
         * @brief Documentacion pendiente.
         */
        template<typename OtherType>
        operator Size<OtherType, Dimension>() const {
            Size<OtherType, Dimension> result;
        
            for(int i=0; i<Dimension; ++i) {
                result.data[i] = static_cast<OtherType>( this->data[i] );
            }
        
            return result;
        }
    };

    typedef Size<double, 3> Size3d;
    typedef Size<float, 3> Size3f;
    typedef Size<int, 3> Size3i;

    typedef Size<double, 2> Size2d;
    typedef Size<float, 2> Size2f;
    typedef Size<int, 2> Size2i;
}

template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::Vector<Type, Size>& Vector);

#include "Size.inl"

#endif  //__EXENG_MATH_Size_HPP__
