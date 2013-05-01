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

#include "../math/TVector.hpp"
#include "../math/TBoundary.hpp"
#include "../Object.hpp"
#include "../graphics/Material.hpp"

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

namespace exeng {
    namespace scenegraph {
        /**
         * @brief El tipo de primitiva a renderizar
         */
        enum class PrimitiveType {
            Point           = 0x00001000,
            PointList       = 0x00001001,
            Line            = 0x00002000,
            LineList        = 0x00002001,
            LineStrip       = 0x00002002,
            LineLoop        = 0x00002003,
            Triangle        = 0x00004000,
            TriangleList    = 0x00004001,
            TriangleStrip   = 0x00004002,
            TriangleFan     = 0x00004003
        };
        
        
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
            PrimitiveType getPrimitiveType() const;
            
            /**
             *  @brief Establece el tipo de primitiva
             */
            void setPrimitiveType(PrimitiveType primitiveType);
            
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
            void setIndexBuffer(IndexBuffer *buffer);
            
            /**
             * @brief Devuelve el buffer de indices actual
             */
            const IndexBuffer* getIndexBuffer() const;
            
            /**
             * @brief Devuelve el buffer de indices actual
             */
            IndexBuffer* getIndexBuffer();
            
            /**
             * @brief Establece el buffer de vertices actual.
             * @param buffer El buffer de vertices a establecer.
             * 
             * Establece el buffer de vertices actual. El MeshPart gana el control
             * de la vida del objeto buffer.
             */
            void setVertexBuffer(VertexBuffer *buffer);
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            const VertexBuffer* getVertexBuffer() const;
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            VertexBuffer* getVertexBuffer();
            
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
