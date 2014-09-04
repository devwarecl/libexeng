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
    template<typename Type, int Dimension>
    Boundary<Type, Dimension>::Boundary() {
        this->edges[0] = Vector<Type, Dimension>(-1);
        this->edges[1] = Vector<Type, Dimension>(1);
    }

    template<typename Type, int Dimension>
    Boundary<Type, Dimension>::Boundary(const Vector<Type, Dimension> &minPoint, const Vector<Type, Dimension> &maxPoint) {
        this->set(minPoint, maxPoint);
    }

    template<typename Type, int Dimension>
    Boundary<Type, Dimension>::Boundary(Type initialSize) {
        this->set(initialSize);
    }
    
    template<typename Type, int Dimension>
    Boundary<Type, Dimension>::Boundary(const Size<Type, Dimension>& size) {
        this->set(size);
    }

    template<typename Type, int Dimension>
    Boundary<Type, Dimension>::Boundary(const Vector<Type, Dimension>& minPoint, const Size<Type, Dimension>& size) {
        this->set(minPoint, size);
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::set(Type initialSize) {
        this->edges[Min].set(static_cast<Type>(0));
        this->edges[Max].set(initialSize);
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::set(const Size<Type, Dimension> &size) {
        this->edges[Min].set(static_cast<Type>(0));
        this->edges[Max].set(size.getPtr());
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::set(const Vector<Type, Dimension> &minPoint, const Size<Type, Dimension> &size) {
        this->edges[Min] = minPoint;
        this->edges[Max] = minPoint + Vector<Type, Dimension>(size.getPtr());
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::set(const Vector<Type, Dimension> &minPoint, const Vector<Type, Dimension> &maxPoint) {
        this->edges[Min] = minPoint;
        this->edges[Max] = maxPoint;
    }

    template<typename Type, int Dimension>
    Vector<Type, Dimension> Boundary<Type, Dimension>::getCenter() const {
        return this->edges[Min] + Vector(this->geSize()) / static_cast<Type>(2);
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::setCenter(const Vector<Type, Dimension>& newCenter) {
        Vector<Type, Dimension> halfSize;
    
        halfSize = Vector<Type, Dimension>( this->geSize() ) / 2;
    
        this->set(-halfSize + newCenter, halfSize + newCenter);
    }

    //!Compute the hyper box size
    template<typename Type, int Dimension>
    Size<Type, Dimension> Boundary<Type, Dimension>::geSize() const {
        auto vsize = this->edges[Max] - this->edges[Min];

        return Size<Type, Dimension>(vsize);
    }

    //!Return the specified edge
    template<typename Type, int Dimension>
    Vector<Type, Dimension> Boundary<Type, Dimension>::getEdge(int PointIndex) const {
        const int LastPoint = Boundary<Type, Dimension>::PointCount-1;

        switch (PointIndex) {
            case 0:         return this->edges[Min];
            case LastPoint: return this->edges[Max]; 
        
            default: {
                Vector<Type, Dimension> Result;
                int Remainder;
            
                //Fill the result...
                for(int i=0; i<Dimension; ++i) {
                    Remainder = PointIndex % 2;
                    PointIndex /= 2;
                
                    Result[i] = edges[Remainder][i];
                }
            
                return Result;
            }
        }
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::seSize(const Vector<Type, Dimension>& newSize) {
        this->set(newSize,  this->getCenter());
    }

    template<typename Type, int Dimension>
    bool Boundary<Type, Dimension>::doIntersect(const Boundary<Type, Dimension>& other) const {   
        for(int i=0; i<Boundary<Type, Dimension>::PointCount; ++i) {
            if ( this->isInside( other.getEdge(i) ) ) {
                return true;
            }
        }
    
        return false;
    }

    template<typename Type, int Dimension>
    bool Boundary<Type, Dimension>::intersect(const Boundary<Type, Dimension>& other) const {
        return this->doIntersect(other) || other.doIntersect(*this);
    }

    template<typename Type, int Dimension>
    bool Boundary<Type, Dimension>::isInside(const Vector<Type, Dimension>& point) const {
        for(int i=0; i<Dimension; ++i) { 
            Type value = point[i];
        
            if (value < this->edges[Min][i]) {
                return false;
            } else if (value > this->edges[Max][i]) {
                return false;
            }
        }
    
        return true;
    }

    template<typename Type, int Dimension>
    bool Boundary<Type, Dimension>::isInside(const Vector<Type, Dimension>& point, Type epsilon) const {
        for(int i=0; i<Dimension; ++i) { 
            Type value = point[i];
        
            if (value - epsilon < this->edges[Min][i]) {
                return false;
            } else if (value + epsilon > this->edges[Max][i]) {
                return false;
            }
        }
    
        return true;
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::expand(const Vector<Type, Dimension>& point) {
        this->edges[Min] = this->edges[Min].minimize(point);
        this->edges[Max] = this->edges[Max].maximize(point);
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::expand(const Boundary<Type, Dimension>& boundary) {
        this->expand(boundary.edges[0]);
        this->expand(boundary.edges[1]);
    }

    template<typename Type, int Dimension>
    inline Vector<Type, Dimension> Boundary<Type, Dimension>::getMin() const {
        return this->edges[0];
    }

    template<typename Type, int Dimension>
    inline Vector<Type, Dimension> Boundary<Type, Dimension>::getMax() const {
        return this->edges[1];
    }
}

template<typename Type, int Dimension>
std::ostream& operator<< (std::ostream &os, const exeng::Boundary<Type, Dimension>& Boundary) {
    return os << "Center : {" << Boundary.getCenter() << "} , Size {" << Boundary.geSize() << "}";
}
