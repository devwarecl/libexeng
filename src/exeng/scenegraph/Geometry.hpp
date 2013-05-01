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

#ifndef __EXENG_SCENEGRAPH_GEOMETRY_HPP__
#define __EXENG_SCENEGRAPH_GEOMETRY_HPP__

#include "../math/TBoundary.hpp"
#include "SceneNodeData.hpp"

namespace exeng {
    namespace scenegraph {
        
		class EXENGAPI Ray;
		struct EXENGAPI IntersectInfo;
		
        /**
         * @brief Geometria abstracta.
         */
        class EXENGAPI Geometry : public SceneNodeData {
        public:
            virtual ~Geometry();
            
            /**
             * @brief Calcula la caja de colision asociada con los ejes.
             * @return Un objeto de tipo Exeng::Math::Boxf, con la caja de colision
             */
            virtual auto getBox() const -> exeng::math::Boxf = 0;
            
            
            /**
             * @brief Detecta la interseccion del objeto geometrico con el rayo indicado.
             * @param point El punto de inicio del rayo.
             * @param direction La direccion a la que el rayo apunta.
             * @return Un valor 'bool'. True si se detecto la interseccion, y False en caso contrario.
             */
			virtual auto hit( const exeng::scenegraph::Ray &ray, exeng::scenegraph::IntersectInfo *intersectInfo) -> bool = 0;
			
			virtual TypeInfo getTypeInfo() const;
        };
    }
}

#endif // __EXENG_SCENEGRAPH_GEOMETRY_HPP__
