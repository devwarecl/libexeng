/**
 * @brief Implementacion de la clase MeshPart
 */

#include "MeshPart.hpp"
#include <boost/checked_delete.hpp>

using exeng::graphics::Material;
using exeng::math::Boxf;

namespace exeng {
    namespace scenegraph {
        
        struct MeshPart::Private {
            const Material *material;
            VertexBuffer *vertexBuffer;
            IndexBuffer *indexBuffer;
            PrimitiveType primitiveType;
            
            Private() : material(nullptr), vertexBuffer(nullptr), indexBuffer(nullptr) {
                this->primitiveType = PrimitiveType::TriangleList;
            }
        };
        
        
        MeshPart::MeshPart() : impl(nullptr) {
            this->impl = new MeshPart::Private();
        }
        
        
        MeshPart::~MeshPart() {
            boost::checked_delete(this->impl);
        }
        
        
        PrimitiveType MeshPart::getPrimitiveType() const {
            return this->impl->primitiveType;
        }
        
        
        void MeshPart::setPrimitiveType(PrimitiveType primitiveType) {
            this->impl->primitiveType = primitiveType;
        }
        
        
        const Material* MeshPart::getMaterial() const {
            return this->impl->material;
        }
        
        
        void MeshPart::setMaterial(const Material* material) {
            this->impl->material = material;
        }
        
        
        void MeshPart::setIndexBuffer(IndexBuffer *buffer) {
            this->impl->indexBuffer = buffer;
        }
        
        
        const IndexBuffer* MeshPart::getIndexBuffer() const {
            return this->impl->indexBuffer;
        }
        
        
        IndexBuffer* MeshPart::getIndexBuffer() {
            return this->impl->indexBuffer;
        }
        
        
        void MeshPart::setVertexBuffer(VertexBuffer *buffer) {
            this->impl->vertexBuffer = buffer;
        }
        
        
        const VertexBuffer* MeshPart::getVertexBuffer() const {
            return this->impl->vertexBuffer;
        }
        
        
        VertexBuffer* MeshPart::getVertexBuffer(){
            return this->impl->vertexBuffer;
        }
        
        
        TypeInfo MeshPart::getTypeInfo() const {
            return TypeInfo::get<MeshPart>();
        }
        
        
        Boxf MeshPart::getBox() const {
            //! TODO: Este metodo debe ser mas generico en el futuro. Por
            //! ahora vamos a asumir que TODOS los bufferes de vertices 
            //! poseen vertices estandar (con posicion, normal y coordenadas de textura).
            
            VertexBuffer *vb = const_cast<VertexBuffer *>(this->getVertexBuffer());
            VertexArray<Vertex> vertices(vb);
            Boxf box(vertices[0].coord, vertices[0].coord);
            
            for(int i=1; i<vertices.size(); ++i) {
                box.expand(vertices[i].coord);
            }
            
            return box;
        }
    }
}
