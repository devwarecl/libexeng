
#ifndef __EXENG_SCENEGRAPH_MESHPART_HPP__
#define __EXENG_SCENEGRAPH_MESHPART_HPP__

#include <cstdint>
#include <vector>

#include "../math/TVector.hpp"
#include "../Object.hpp"
#include "../graphics/Material.hpp"

namespace exeng {
    namespace scenegraph {
        
        /**
         *  @brief El tipo de primitiva a renderizar
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
        
        
        // typedef std::vector<Vertex> VertexArray;
        // typedef std::vector<int> IntArray;
        
        /**
         *  @brief Seccion de un modelo tridimensional. Referencia a un material
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
             *  @brief Establece el material actual de renderizacion
             */
            void setMaterial(const exeng::graphics::Material* material);
            
            
            
            /**
             *  @brief Establece el arreglo de indices actual. 
             */
            
            // void setIndexArray(const IntArray &indexArray);
            
            
            /**
             * @brief Devuelve una copia del arreglo de indices actual
             */
            // const IntArray& getIndexArray() const;
            
            /**
             * @brief Comprueba si esta parte posee indices.
             */
            
            bool hasIndices() const;
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            // void setVertexArray(const VertexArray &vertexArray);
            
            
            /**
             * @brief Establece el arreglo de vertices actual
             */
            // const VertexArray& getVertexArray() const;
            
            
            virtual TypeInfo getTypeInfo() const;
            
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif
