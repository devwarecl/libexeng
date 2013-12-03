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


#ifndef __EXENG_MATH_TSIZE_HPP__
#define __EXENG_MATH_TSIZE_HPP__

#include "TVector.hpp"
#include <iosfwd>

namespace exeng { namespace math {

template<typename Type, int Dimension>  class TSizeBase;

template<typename Type> class TSizeBase<Type, 2> {
public:
    union {
        struct { Type width, height; };
        Type data[2];
    };
    
public:
    TSizeBase() {}

    TSizeBase(Type width, Type height) {
        this->set(width, height);
    }

    void set(Type width, Type height) {
        this->width = width;
        this->height = height;
    }
};


template<typename Type> class TSizeBase<Type, 3> {
public:
    union {
        struct { Type width, height, depth; };
        Type data[3];
    };

public:
    TSizeBase() {}

    TSizeBase(Type width, Type height, Type depth) {
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
class TSize : public TSizeBase<Type, Dimension> {
public:
    typedef TSize<Type, Dimension> Size;
    typedef TVector<Type, Dimension> Vector;
    
public:
    using TSizeBase<Type, Dimension>::set;

    /**
     * @brief Documentacion pendiente.
     */
    TSize();
    
    /**
     * @brief Documentacion pendiente.
     */
    explicit TSize(Type baseSize);
    
    /**
     * @brief Documentacion pendiente.
     */
    explicit TSize(const Type* arrIn);
    
    /**
     * @brief Documentacion pendiente.
     */
    explicit TSize(const Vector &inVect);
    
    /**
     * @brief Documentacion pendiente.
     */
    TSize(Type Width, Type Height);
    
    /**
     * @brief Documentacion pendiente.
     */
    TSize(Type Width, Type Height, Type Depth);
    
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
    void set(const Vector &inVect);
    

    /**
     * @brief Documentacion pendiente.
     */
    bool operator!= (const Size& rhs) const;
    
    /**
     * @brief Documentacion pendiente.
     */
    bool operator== (const Size& rhs) const;
    
    /**
     * @brief Documentacion pendiente.
     */
    bool operator> (const Size& rhs) const;
    
    /**
     * @brief Documentacion pendiente.
     */
    bool operator< (const Size& rhs) const;
    
    /**
     * @brief Documentacion pendiente.
     */
    bool operator>= (const Size& rhs) const;
    
    /**
     * @brief Documentacion pendiente.
     */
    bool operator<= (const Size& rhs) const;
    
    
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
    operator TVector<Type, Dimension>() const;
    

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
    operator TSize<OtherType, Dimension>() const {
        TSize<OtherType, Dimension> result;
        
        for(int i=0; i<Dimension; ++i) {
            result.data[i] = static_cast<OtherType>( this->data[i] );
        }
        
        return result;
    }
};

typedef TSize<double, 3> Size3d;
typedef TSize<float, 3> Size3f;
typedef TSize<int, 3> Size3i;

typedef TSize<double, 2> Size2d;
typedef TSize<float, 2> Size2f;
typedef TSize<int, 2> Size2i;

}}
        
template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::math::TVector<Type, Size>& Vector);

#include "TSize.inl"

#endif  //__EXENG_MATH_TSIZE_HPP__
