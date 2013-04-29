
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
            PointList,
            LineList,
            LineStrip,
            LineLoop,
            TriangleList,
            TriangleStrip,
            TriangleFan
        };
        
        
        /**
         * @brief Seccion de un modelo tridimensional. Referencia a un material
         * 
         * @TODO Definir de forma mas apropiada los setters y getters para los buffers de 
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
