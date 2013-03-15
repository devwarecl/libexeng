/**
 * @brief Documentacion pendiente.
 */

#ifndef __EXENG_MATH_TBOUNDARY_HPP__
#define __EXENG_MATH_TBOUNDARY_HPP__

#include "TVector.hpp"
#include "TSize.hpp"

namespace exeng {
    namespace math {
        namespace detail {
            /**
             * @brief Calcula una potencia para numeros enteros.
             * @tparam Base La base con la cual calcular la potencia.
             * @tparam Exp El exponente para calcular la potencia.
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
        class TBoundary {
        public:
            enum { PointCount = detail::Power<2, Dimension>::Value };
            
        public:
            typedef TBoundary<Type, Dimension>  Boundary;
            typedef TVector<Type, Dimension>    Vector;
            typedef TSize<Type, Dimension>      Size;
            

        public:
            /**
             * @brief Constructor por defecto
             */
            TBoundary();
            
            /**
             * @brief Initializa la frontera usando un mismo valor para el tamanio en todas las dimensiones.
             * @param initialSize El tamanio.
             */
            explicit TBoundary(Type initialSize);
            

            /**
             * @brief Initializa la frontera con el tamanio indicado en todas las dimensiones
             * @param initialSize El tamanio.
             */
            explicit TBoundary(const Size& size);
            

            /**
             * @brief
             */
            TBoundary(const Vector& minPoint, const Vector& maxPoint);
            
            /**
             * @brief
             */
            TBoundary(const Vector& minPoint, const Size& size);
            
            /**
             * @brief
             */
            void set(Type initialSize);
            
            /**
             * @brief
             */
            void set(const Size& size);
            
            /**
             * @brief
             */
            void set(const Vector& minPoint, const Vector& maxPoint);
            
            /**
             * @brief
             */
            void set(const Vector& minPoint, const Size& size);
            
            /**
             * @brief Devuelve el valor central de la frontera
             * @returns El centro de la frontera
             */
            Vector getCenter() const;
            
            /**
             * @brief Establece el nuevo centro de la frontera.
             * @param newCenter El nuevo centro de la frontera.
             */
            void setCenter(const Vector& newCenter);
            
            /**
             * @brief Devuelve el tamanio de la frontera
             * @return El tamanio de la frontera, encapsulado como un Size.
             */
            Size getSize() const;
            
            /**
             * @brief Devuelve un punto que se encuentra en una de las esquinas de la frontera.
             * @return El punto que se encuentra en la esquina indicada
             */
            Vector getEdge(int PointIndex) const;
            
            /**
             * @brief Establece el tamanio de la frontera, sin cambiar su posicion espacial.
             * @param newSize El nuevo tamanio de la frontera.
             */
            void setSize(const Vector& newSize);
            
            /**
             * @brief Comprueba si la frontera se intersecta con otra.
             * @return Booleano, true si existe interseccion entre las fronteras, y false en caso contrario.
             */
            bool intersect(const Boundary& other) const;

            /**
             * @brief Comprueba si el punto indicado se encuentra dentro o en los confines de la frontera.
             * @return Booleano, true si el punto esta dentro de la frontera, y false en caso contrario.
             */
            bool isInside(const Vector& point) const;

            /**
             * @brief Expande las proporciones de la frontera, de tal forma que el punto indicado se encuentre dentro de ella. 
             * @param point El punto que 
             */
            void expand(const Vector& point);

            /**
             * @brief Expande las proporciones de la frontera, de tal forma que la frontera indicada
             */
            void expand(const Boundary& other);
            
        private:
            bool doIntersect(const Boundary& other) const;
            
        private:
            enum  { Min, Max };
			Vector edges[2];
        };
        

        template<typename Type, int Dimension>
        std::ostream& operator<< (std::ostream &os, const TBoundary<Type, Dimension>& Boundary);
        
        typedef TBoundary<float, 3> Boxf;
        typedef TBoundary<int, 3> Boxi;
        typedef TBoundary<double, 3> Boxd;
        
        typedef TBoundary<float, 2> Rectf;
        typedef TBoundary<int, 2> Recti;
        typedef TBoundary<double, 2> Rectd;
        
        typedef TBoundary<float, 1> Intervalf;
        typedef TBoundary<int, 1> Intervali;
        typedef TBoundary<double, 1> Intervald;
    }
}

#include "TBoundary.inl"

#endif  //__EXENG_MATH_TBoundary_HPP__
