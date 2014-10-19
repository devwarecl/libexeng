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

#include <iostream>
#include <iomanip>
#include <cassert>

namespace exeng { 
    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size() {}


    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size(Type baseSize) {
        this->set(baseSize);
    }


    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size(const Type* arrIn) {
        this->set(arrIn);
    }


    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size(const Vector<Type, Dimension> &inVect) {
        this->set(inVect);
    }


    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size(Type Width, Type Height) {
        this->set(Width, Height);
    }


    template<typename Type, int Dimension>
    Size<Type, Dimension>::Size(Type Width, Type Height, Type Depth) {
        this->set(Width, Height, Depth);
    }

    template<typename Type, int Dimension>
    void Size<Type, Dimension>::set(Type baseSize) {
        for(int i=0; i<Dimension; ++i) {
            this->data[i] = baseSize;
        }
    }

    template<typename Type, int Dimension>
    void Size<Type, Dimension>::set(const Type* arrIn) {
        for(int i=0; i<Dimension; ++i) {
            this->data[i] = arrIn[i];
        }
    }

    template<typename Type, int Dimension>
    void Size<Type, Dimension>::set(const Vector<Type, Dimension> &inVect) {
        this->set(inVect.getPtr());
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator!= (const Size<Type, Dimension>& rhs) const {
        return !(*this == rhs);
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator== (const Size<Type, Dimension>& rhs) const {
        return exeng::arrayCompare<Type, Dimension>(this->data, rhs.data);
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator> (const Size<Type, Dimension>& rhs) const {
        auto accum1 = exeng::arraySum<Type, Dimension>(rhs.data);
        auto accum2 = exeng::arraySum<Type, Dimension>(this->data);

        return accum1 > accum2;
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator< (const Size<Type, Dimension>& rhs) const {
        return !(*this > rhs);
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator>= (const Size<Type, Dimension>& rhs) const {
        return (*this > rhs) || (*this == rhs);
    }

    template<typename Type, int Dimension>
    bool Size<Type, Dimension>::operator<= (const Size<Type, Dimension>& rhs) const { 
        return (*this < rhs) || (*this == rhs);
    }

    template<typename Type, int Dimension>
    Type& Size<Type, Dimension>::operator[] (int index) {
        assert(index < Dimension);
        return this->data[index];
    }

    template<typename Type, int Dimension>
    const Type& Size<Type, Dimension>::operator[] (int index) const {
        assert(index < Dimension);
        return this->data[index];
    }

    template<typename Type, int Dimension>
    Size<Type, Dimension>::operator Vector<Type, Dimension>() const {
        return Vector<Type, Dimension>(this->data);
    }

    template<typename Type, int Dimension>
    Type* Size<Type, Dimension>::getPtr() {
        return this->data;
    }

    template<typename Type, int Dimension>            
    const Type* Size<Type, Dimension>::getPtr() const {
        return this->data;
    }
}


template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::Size<Type, Size>& size) {
    for(int i=0; i<Size; ++i) {
        os << std::fixed << std::setprecision( 4 ) << size[i];
        
        if (i + 1 != Size) {
            os << ", ";
        }
    }
    
    return os;
}