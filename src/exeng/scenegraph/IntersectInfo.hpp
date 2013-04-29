/**
 * @brief Definicion de la estructura IntersectInfo
 */

#ifndef __EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
#define __EXENG_SCENEGRAPH_INTERSECTINFO_HPP__

#include "../math/TVector.hpp"
#include "../graphics/Material.hpp"

namespace exeng {
    namespace scenegraph {
        /**
         * @brief Almacena informacion general sobre la interseccion de un rayo 
		 * y un objeto determinado
         */
        struct IntersectInfo {
            /**
             * @brief Existio interseccion?
             */
            bool intersect;
            
            /**
             * @brief Coordenadas parametricas de los puntos de interseccion
             */
            float parametricCoord;

			/**
			 * @brief Normal de la superficie
			 */
			exeng::math::Vector3f surfaceNormal;

			/**
			 * @brief Material de la superficie en el punto de interseccion
			 */
			const exeng::graphics::Material* surfaceMaterial;


			IntersectInfo();
        };


		inline IntersectInfo::IntersectInfo() {
			// Inicializar los parametros por defecto
			this->intersect = false;
			this->parametricCoord = 0.0f;
			this->surfaceNormal.set(0.0f);
			this->surfaceMaterial = nullptr;
		} 
    }
}

#endif  //__EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
