/**
 * @brief Define la clase Ray.
 */

#ifndef __EXENG_SCENEGRAPH_RAY_HPP__
#define __EXENG_SCENEGRAPH_RAY_HPP__

#include <iosfwd>

#include "../math/TVector.hpp"
#include "../Config.hpp"

namespace exeng {
    namespace scenegraph {   
        /**
         * @brief Abstraccion de un rayo.
         *
         * Encapsula del conjunto de operaciones aplicables, o deviradas de la utilizacion de un rayo
         * en un entorno tridimensional.
         */
        class Ray {
        public:
            /**
             * @brief Inicializa el rayo apuntando en direccion al eje Z positivo (direccion hacia adelante)
             */
            Ray();
            
			/**
			 * @brief Inicializa el rayo, usando un punto de base y una direccion arbitrarias
			 */
			Ray(const exeng::math::Vector3f& point, const exeng::math::Vector3f& direction);

            /**
             * @brief Establece el punto tomado como base del rayo.
             * @param point
             */
            auto setPoint(const exeng::math::Vector3f& point) -> void;

			/**
             * @brief Establece las coordenadas del punto base del rayo
             * @param x La coordenada X del rayo.
			 * @param y La coordenada Y del rayo.
			 * @param z La coordenada Z del rayo.
             */
			auto setPoint(float x, float y, float z) -> void;

			/**
             * @brief Establece la coordenada X del rayo
             * @param value La coordenada X del rayo.
			 */
			auto setPointX(float value) -> void;

			/**
             * @brief Establece la coordenada Y del rayo
             * @param value La coordenada Y del rayo.
			 */
			auto setPointY(float value) -> void;

			/**
             * @brief Establece la coordenada Z del rayo
             * @param value La coordenada X del rayo.
			 */
			auto setPointZ(float value) -> void;

            /**
             * @brief Devuelve el punto base del rayo.
             * @return 
             */
            auto getPoint() const -> exeng::math::Vector3f;
            
			/**
             * @brief Devuelve la coordenada X del punto base del rayo.
			 */
			auto getPointX() const -> float;

			/**
             * @brief Devuelve la coordenada Y del punto base del rayo.
			 */
			auto getPointY() const -> float;

			/**
             * @brief Devuelve la coordenada Z del punto base del rayo.
			 */
			auto getPointZ() const -> float;

            /**
             * @brief Establece la direccion del rayo.
             * @param direction
             */
            auto setDirection(const exeng::math::Vector3f& direction) -> void;
            
			/**
             * @brief Establece la direccion del rayo.
             */
            auto setDirection(float x, float y, float z) -> void;

			/**
             * @brief Establece la coordenada X de la direccion del rayo
             
            auto setDirectionX(float value) -> void;

             * @brief Establece la coordenada Y de la direccion del rayo
             
            auto setDirectionY(float value) -> void;

             * @brief Establece la coordenada Z de la direccion del rayo
             */
            auto setDirectionZ(float value) -> void;

			/**
             * @brief Devuelve la coordenada X de la direccion del rayo
             */
            auto getDirectionX() const -> float;

			/**
             * @brief Devuelve la coordenada Y de la direccion del rayo
             */
            auto getDirectionY() const -> float;

			/**
             * @brief Devuelve la coordenada Z de la direccion del rayo
             */
            auto getDirectionZ() const -> float;

            /**
             * @brief Devuelve la direccion del rayo.
             * @return 
             */
            auto getDirection() const -> exeng::math::Vector3f;

            /**
             * @brief Calcula el punto que se encuentra a 't' unidades. 
             * 
             * Toma como base el punto base del rayo y la direccion.
             * Es posible que la distancia entre el punto base del rayo y el punto calculado por este
             * metodo es muy cercano a 't', por lo que a la hora de hacer comparaciones, es necesario
             * usar un valor de tolerancia 'epsilon'.
             * @param t
             * @return 
             */
            auto getPointAt(float t) const -> exeng::math::Vector3f;
            
            /**
             * @brief Establece los atributos del rayo.
             * @param point El punto base del rayo.
             * @param direction La direccion del rayo. 
             */
            auto setAttributes(const exeng::math::Vector3f& point, const exeng::math::Vector3f& direction) -> void;
            
        private:
            /**
             * @brief Punto base. No tiene restricciones en los valores que puede contener 
             */
            exeng::math::Vector3f point;	
            
            /**
             * @brief Direccion. Siempre debe ser siempre un vector unitario.
             */
            exeng::math::Vector3f direction;	
        };
    }
}

std::ostream& operator<< (std::ostream& os, const exeng::scenegraph::Ray& ray);

#include "Ray.inl"

#endif	//__EXENG_SCENEGRAPH_RAY_HPP__
