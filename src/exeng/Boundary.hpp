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

#ifndef __EXENG_MATH_Boundary_HPP__
#define __EXENG_MATH_Boundary_HPP__

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
        SizeType geSize() const;
        
        /**
         * @brief Devuelve un punto que se encuentra en una de las esquinas de la frontera.
         * @return El punto que se encuentra en la esquina indicada
         */
        VectorType getEdge(int PointIndex) const;
    
        /**
         * @brief Establece el tamanio de la frontera, sin cambiar su posicion espacial.
         * @param newSize El nuevo tamanio de la frontera.
         */
        void seSize(const VectorType& newSize);
    
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

template<typename Type, int Dimension>
std::ostream& operator<< (std::ostream &os, const exeng::Boundary<Type, Dimension>& Boundary);

#include "Boundary.inl"

#endif  //__EXENG_MATH_Boundary_HPP__
