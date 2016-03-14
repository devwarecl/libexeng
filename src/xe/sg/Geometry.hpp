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

#include <memory>
#include <xe/Boundary.hpp>
#include <xe/sg/SceneNodeData.hpp>
#include <xe/sg/Renderable.hpp>

namespace xe { namespace sg {
        
	class Ray;
	struct IntersectInfo;

	/**
	 * @brief Abstract Geometry class.
	 */
	class EXENGAPI Geometry : public Renderable {
	public:
		virtual ~Geometry();

		/**
		 * @brief Calcula la caja de colision asociada con los ejes.
		 * @return Un objeto de tipo Exeng::Boxf, con la caja de colision
		 */
		virtual Boxf getBox() const = 0;
         
		/**
		 * @brief Detecta la interseccion del objeto geometrico con el rayo indicado.
		 * @param point El punto de inicio del rayo.
		 * @param direction La direccion a la que el rayo apunta.
		 * @return Un valor 'bool'. True si se detecto la interseccion, y False en caso contrario.
		 */
		virtual bool hit( const xe::sg::Ray &ray, xe::sg::IntersectInfo *intersectInfo) = 0;
			
		virtual TypeInfo getTypeInfo() const;

		virtual void renderWith(xe::sg::Renderer *renderer) override;
	};

	typedef std::unique_ptr<Geometry> GeometryPtr;
}}

#endif // __EXENG_SCENEGRAPH_GEOMETRY_HPP__
