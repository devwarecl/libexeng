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

#ifndef __EXENG_SCENEGRAPH_MESHPART_HPP__
#define __EXENG_SCENEGRAPH_MESHPART_HPP__

#include <cstdint>
#include <vector>

#include <exeng/Object.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/Primitive.hpp>

namespace exeng {
    namespace scenegraph {

        /**
         * @brief Seccion de un modelo tridimensional. Referencia a un material
         * 
         * @todo Definir de forma mas apropiada los setters y getters para los buffers de 
         * vertices e indices.
         */
        class EXENGAPI MeshPart : public Object {
        public:            
            MeshPart();
            
            virtual ~MeshPart();
            
            /**
             *  @brief Devuelve el tipo de primitiva
             */
            exeng::graphics::Primitive::Enum getPrimitiveType() const;
            
            /**
             *  @brief Establece el tipo de primitiva
             */
            void setPrimitiveType(exeng::graphics::Primitive::Enum primitiveType);
            
            /**
             *  @brief Devuelve el material actual de renderizacion
             */
            const exeng::graphics::Material* getMaterial() const;
            
            /**
             *  @brief Establece el material actual de renderizacion.
             */
            void setMaterial(const exeng::graphics::Material* material);
            
            /**
             * @brief Establece el buffer de indices actual.
             * @param buffer El buffer de indices a establecer.
             * 
             * Establece el buffer de vertices actual. El MeshPart gana el control
             * de la vida del objeto buffer. Para efectos de renderizacion, este buffer 
             * es completamente opcional, 
             */            
            void setIndexBuffer( exeng::graphics::IndexBuffer *buffer);
            
            /**
             * @brief Devuelve el buffer de indices actual
             */
            const exeng::graphics::IndexBuffer* getIndexBuffer() const;
            
            /**
             * @brief Devuelve el buffer de indices actual
             */
            exeng::graphics::IndexBuffer* getIndexBuffer();
            
            /**
             * @brief Establece el buffer de vertices actual.
             * @param buffer El buffer de vertices a establecer.
             * 
             * Establece el buffer de vertices actual. El MeshPart gana el control
             * de la vida del objeto buffer.
             */
            void setVertexBuffer(exeng::graphics::VertexBuffer *buffer);
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            const exeng::graphics::VertexBuffer* getVertexBuffer() const;
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            exeng::graphics::VertexBuffer* getVertexBuffer();
            
            /**
             * @brief Calcula la caja de colision de la parte actual
             */
            exeng::math::Boxf getBox() const;
            
            virtual TypeInfo getTypeInfo() const;
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif
