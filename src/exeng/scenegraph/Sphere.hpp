
#ifndef __EXENG_SCENEGRAPH_SPHERE_HPP__
#define __EXENG_SCENEGRAPH_SPHERE_HPP__

#include "../math/TVector.hpp"

namespace exeng
{
    namespace scenegraph
    {
        class Ray;
        struct IntersectInfo;

        /**
         * @brief Esfera en el espacio tridimensional.
         */
        class Sphere
        {
        public:
            
            /**
             * @brief Inicializa una esfera en el origen y con radio unitario.
             */ 
            Sphere();
            
            /**
             * @brief Inicializa una esfera en el origen, y con radio arbitrario
             */
            explicit Sphere(float radius);
            
            /**
             * @brief Inicializa una esfera cuyo centro este en la posicion y con el radio indicados.
             * @param radius El radio de la esfera, en unidades de mundo.
             * @param center La posicion en el espacio, en donde estara ubicado el centro de la esfera.
             */
            explicit Sphere(float radius, const exeng::math::Vector3f &center);
            
            /**
             * @brief Inicializa todos los atributos de la esfera de una sola vez.
             */
            auto setAttributes(float radius, const exeng::math::Vector3f &center) -> void;
            
            /**
             * @brief Establece el radio de la esfera
             */
            auto setRadius(float radius) -> void;
            
            /**
             * @brief Establece la posicion en donde estara ubicado el centro de la esfera.
             */
            auto setCenter(const exeng::math::Vector3f &center) -> void;
            
            /**
             * @brief Devuelve el radio actual de la esfera
             */
            auto getRadius() const -> float;
            
            /**
             * @brief Devuelve la posicion en donde esta ubicado el centro de la esfera
             */
            auto getCenter() const -> exeng::math::Vector3f;
            
            /**
             * @brief Calcula la interseccion entre el rayo indicado, y la esfera.
             */
            auto intersect(const Ray& ray, IntersectInfo *intersectInfo=NULL) -> bool;
            
            
            /**
             * @brief Comprueba si dos esferas son iguales.
             */
            bool operator== (const Sphere &sphere) const;
            
            
            /**
             * @brief Comprueba si dos esferas son distintas.
             */
            bool operator!= (const Sphere &sphere) const;
            
            
        private:
            exeng::math::Vector3f center;
            float radius;
        };
    }
}

std::ostream& operator<< (std::ostream &os, const exeng::scenegraph::Sphere &sphere);

#include "Sphere.inl"

#endif  //__EXENG_SCENEGRAPH_SPHERE_HPP__
