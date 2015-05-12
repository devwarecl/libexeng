/**
 * @file Boundary.hpp
 * @brief Boundary class template definition
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_MATH_BOUNDARY_HPP__
#define __EXENG_MATH_BOUNDARY_HPP__

#include "Vector.hpp"
#include "Size.hpp"

namespace exeng { 

    namespace detail {
        /**
         * @brief Compile-time power compute.
         */
        template<int Base, int Exp> struct Power {
            enum { Value = Base * Power<Base, Exp - 1>::Value };
        };
    
        template<int Base> struct Power<Base, 0> {
            enum { Value = 1 };
        };
    }

    /**
     * @brief Define una frontera alineada con los ejes espaciales, en cualquier dimension
     * @tparam Type El tipo de datos para 
     * @tparam Dimension
     */
    template<typename Type, int Dimension>
    class Boundary {
    public:
        enum { PointCount = detail::Power<2, Dimension>::Value };
    
    public:
        typedef Boundary<Type, Dimension>  BoundaryType;
        typedef Vector<Type, Dimension>    VectorType;
        typedef Size<Type, Dimension>      SizeType;
        
    public:
        /**
         * @brief Constructor por defecto
         */
        Boundary();
        
        /**
         * @brief Initializa la frontera usando un mismo valor para el tamanio en todas las dimensiones.
         * @param initialSize El tamanio.
         */
        explicit Boundary(Type initialSize);
        
        /**
         * @brief Initializa la frontera con el tamanio indicado en todas las dimensiones
         * @param initialSize El tamanio.
         */
        explicit Boundary(const SizeType& size);
        
        /**
         * @brief
         */
        Boundary(const VectorType& minPoint, const VectorType& maxPoint);
    
        /**
         * @brief
         */
        Boundary(const VectorType& minPoint, const SizeType& size);
    
        /**
         * @brief
         */
        void set(Type initialSize);
    
        /**
         * @brief
         */
        void set(const SizeType& size);
    
        /**
         * @brief
         */
        void set(const VectorType& minPoint, const VectorType& maxPoint);
    
        /**
         * @brief
         */
        void set(const VectorType& minPoint, const SizeType& size);
    
        /**
         * @brief Devuelve el valor central de la frontera
         * @returns El centro de la frontera
         */
        VectorType getCenter() const;
    
        /**
         * @brief Establece el nuevo centro de la frontera.
         * @param newCenter El nuevo centro de la frontera.
         */
        void setCenter(const VectorType& newCenter);
    
        /**
         * @brief Devuelve el tamanio de la frontera
         * @return El tamanio de la frontera, encapsulado como un Size.
         */
        SizeType getSize() const;
        
        /**
         * @brief Devuelve un punto que se encuentra en una de las esquinas de la frontera.
         * @return El punto que se encuentra en la esquina indicada
         */
        VectorType getEdge(int PointIndex) const;
    
        /**
         * @brief Establece el tamanio de la frontera, sin cambiar su posicion espacial.
         * @param newSize El nuevo tamanio de la frontera.
         */
        void setSize(const VectorType& newSize);
    
        /**
         * @brief Comprueba si la frontera se intersecta con otra.
         * @return Booleano, true si existe interseccion entre las fronteras, y false en caso contrario.
         */
        bool intersect(const BoundaryType& other) const;

        /**
         * @brief Comprueba si el punto indicado se encuentra dentro o en los confines de la frontera.
         * @return Booleano, true si el punto esta dentro de la frontera, y false en caso contrario.
         */
        bool isInside(const VectorType& point) const;

	    /**
         * @brief Check if the point is the interior of the boundary. Check using epsilon-based values
         */
	    bool isInside(const VectorType& point, Type epsilon) const;

        /**
         * @brief Make bigger the boundary if the point doesn't be inside.
         */
        void expand(const VectorType& point);

        /**
         * @brief Make bigger the boundary if the point doesn't be inside.
         */
        void expand(const BoundaryType& other);
    
        /**
         * @brief Get the min limit of the boundary.
         * @return 
         */
        VectorType getMin() const;
    
        /**
         * @brief Get the max limit of the boundary.
         * @return 
         */
        VectorType getMax() const;
        
        friend std::ostream& operator<< (std::ostream &os, const exeng::Boundary<Type, Dimension>& Boundary)
        {
            return os << "Center: {" << Boundary.getCenter() << "}, Size: {" << Boundary.getSize() << "}";
        }
        
    private:
        bool doIntersect(const BoundaryType& other) const;
    
    private:
        enum  { Min, Max };
        VectorType edges[2];
    };
    
    typedef Boundary<float, 3> Boxf;
    typedef Boundary<int, 3> Boxi;
    typedef Boundary<double, 3> Boxd;

    typedef Boundary<float, 2> Rectf;
    typedef Boundary<int, 2> Recti;
    typedef Boundary<double, 2> Rectd;
}


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
        return this->edges[Min] + Vector<Type, Dimension>(this->getSize()) / static_cast<Type>(2);
    }

    template<typename Type, int Dimension>
    void Boundary<Type, Dimension>::setCenter(const Vector<Type, Dimension>& newCenter) {
        Vector<Type, Dimension> halfSize;
		
        halfSize = Vector<Type, Dimension>( this->getSize() ) / 2;
		
        this->set(-halfSize + newCenter, halfSize + newCenter);
    }

    //!Compute the hyper box size
    template<typename Type, int Dimension>
    Size<Type, Dimension> Boundary<Type, Dimension>::getSize() const {
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
    void Boundary<Type, Dimension>::setSize(const Vector<Type, Dimension>& newSize) {
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
        this->edges[Min] = maximize(this->edges[Min], point);
        this->edges[Max] = minimize(this->edges[Max], point);
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

#endif  //__EXENG_MATH_BOUNDARY_HPP__
