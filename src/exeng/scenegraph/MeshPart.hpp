
#ifndef __EXENG_SCENEGRAPH_MESHPART_HPP__
#define __EXENG_SCENEGRAPH_MESHPART_HPP__

#include <cstdint>
#include <vector>
#include "../math/TVector.hpp"
#include "../graphics/Material.hpp"

namespace exeng {
    namespace scenegraph {
        
        /**
         *  @brief El tipo de primitiva
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
         *  @brief Estructura de un vertice de pruebas
         */
        struct Vertex {
            exeng::math::Vector3f coord;
            exeng::math::Vector3f normal;
            exeng::math::Vector2f texCoord;
        };
        
        
        /**
         *  @brief Seccion de un modelo tridimensional. Referencia a un material
         */
        class EXENGAPI MeshPart {
        public:            
            MeshPart(std::uint32_t vertexCount);
            
            virtual ~MeshPart();
            
            /**
             *  @brief Devuelve la cantidad de vertices de la seccion.
             */
            std::uint32_t getVertexCount() const;
            
            
            /**
             *  @brief Devuelve un puntero al arreglo de vertices
             */
            Vertex* getVertex(std::uint32_t index);
            
            
            /**
             *  @brief Devuelve un puntero al arreglo de vertices
             */
            const Vertex* getVertex(std::uint32_t index) const;
            
            /**
             *  @brief Devuelve el tipo de primitiva
             */
            PrimitiveType getPrimitiveType() const;
            
            
            /**
             *  @brief Establece el tipo de primitiva
             */
            void setPrimitiveType(PrimitiveType pt);
            
            
            /**
             *  @brief Devuelve el material actual
             */
            const exeng::graphics::Material* getMaterial() const;
            
            
            /**
             *  @brief Establece el material actual
             */
            void setMaterial(const exeng::graphics::Material* material);
            
            
            /**
             *  @brief Establece el arreglo de indices actual. 
             */
            
            
        private:
            struct Private;
            Private *impl;
        };
    }
}

#endif
