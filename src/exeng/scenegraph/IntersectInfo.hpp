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
            float distance;

			/**
			 * @brief Normal de la superficie
			 */
			exeng::math::Vector3f normal;
            
            
            /**
             * @brief El punto en la superficie donde se produjo la interseccion
             */
            exeng::math::Vector3f point;
            
            
			/**
			 * @brief Material de la superficie en el punto de interseccion
			 */
			const exeng::graphics::Material* materialPtr;


			IntersectInfo();
        };

        
		inline IntersectInfo::IntersectInfo() {
			this->intersect = false;
			this->distance = 0.0f;
			this->normal = exeng::math::Vector3f(0.0f);
            this->point = exeng::math::Vector3f(0.0f);
			this->materialPtr = nullptr;
		} 
    }
}

#endif  //__EXENG_SCENEGRAPH_INTERSECTINFO_HPP__
