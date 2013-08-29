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

namespace exeng { namespace math {

template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize() {}


template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize(Type baseSize) {
    this->set(baseSize);
}


template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize(const Type* arrIn) {
    this->set(arrIn);
}


template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize(const TVector<Type, Dimension> &inVect) {
    this->set(inVect);
}


template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize(Type Width, Type Height) {
    this->set(Width, Height);
}


template<typename Type, int Dimension>
TSize<Type, Dimension>::TSize(Type Width, Type Height, Type Depth) {
    this->set(Width, Height, Depth);
}


template<typename Type, int Dimension>
void TSize<Type, Dimension>::set(Type baseSize) {
    for(int i=0; i<Dimension; ++i) {
        this->data[i] = baseSize;
    }
}


template<typename Type, int Dimension>
void TSize<Type, Dimension>::set(const Type* arrIn) {
    for(int i=0; i<Dimension; ++i) {
        this->data[i] = arrIn[i];
    }
}


template<typename Type, int Dimension>
void TSize<Type, Dimension>::set(const TVector<Type, Dimension> &inVect) {
    this->set(inVect.getPtr());
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator!= (const TSize<Type, Dimension>& rhs) const {
    return !(*this == rhs);
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator== (const TSize<Type, Dimension>& rhs) const {
    return exeng::math::arrayCompare<Type, Dimension>(this->data, rhs.data);
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator> (const TSize<Type, Dimension>& rhs) const {
    auto accum1 = exeng::math::arraySum<Type, Dimension>(rhs.data);
    auto accum2 = exeng::math::arraySum<Type, Dimension>(this->data);

    return accum1 > accum2;
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator< (const TSize<Type, Dimension>& rhs) const {
    return !(*this > rhs);
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator>= (const TSize<Type, Dimension>& rhs) const {
    return (*this > rhs) || (*this == rhs);
}


template<typename Type, int Dimension>
bool TSize<Type, Dimension>::operator<= (const TSize<Type, Dimension>& rhs) const { 
    return (*this < rhs) || (*this == rhs);
}

template<typename Type, int Dimension>
Type& TSize<Type, Dimension>::operator[] (int index) {
    assert(index < Dimension);
    return this->data[index];
}


template<typename Type, int Dimension>
const Type& TSize<Type, Dimension>::operator[] (int index) const {
    assert(index < Dimension);
    return this->data[index];
}


template<typename Type, int Dimension>
TSize<Type, Dimension>::operator TVector<Type, Dimension>() const {
    return TVector<Type, Dimension>(this->data);
}


template<typename Type, int Dimension>
Type* TSize<Type, Dimension>::getPtr() {
    return this->data;
}


template<typename Type, int Dimension>            
const Type* TSize<Type, Dimension>::getPtr() const {
    return this->data;
}

}}


template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::math::TSize<Type, Size>& size) {
    os << "(";
    
    for(int i=0; i<Size; ++i) {
        os << std::fixed << std::setprecision( 4 ) << size[i];
        
        if (i + 1 != Size) {
            os << ", ";
		}
    }
    
    os << ")";
    
    return os;
}
