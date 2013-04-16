/**
 * @brief Implementacion de la clase MeshPart
 */

#include "MeshPart.hpp"
#include <boost/checked_delete.hpp>

using exeng::graphics::Material;

namespace exeng {
    namespace scenegraph {
        
        struct MeshPart::Private {
            const Material *material;
            // VertexArray vertexArray;
            // IntArray indexArray;
            PrimitiveType primitiveType;
        };
        
        
        MeshPart::MeshPart() : impl(nullptr) {
            this->impl = new MeshPart::Private();
        }
        
        /*
        MeshPart::MeshPart(const VertexArray &vertexArray) : impl(nullptr)  {
            this->impl = new MeshPart::Private();
            
            this->setVertexArray(vertexArray);
        }
        
        
        MeshPart::MeshPart(const VertexArray &vertexArray, const IntArray &indexArray) : impl(nullptr)  {
            this->impl = new MeshPart::Private();
            
            this->setVertexArray(vertexArray);
            this->setIndexArray(indexArray);
        }
        */
        
        
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
        
        
        /*
        void MeshPart::setIndexArray(const IntArray &indexArray) {
            this->impl->indexArray = indexArray;
        }
        
        
        
        const IntArray& MeshPart::getIndexArray() const {
            return this->impl->indexArray;
        }
        
        
        void MeshPart::setVertexArray(const VertexArray &vertexArray) {
            this->impl->vertexArray = vertexArray;
        }
        
        
        const VertexArray& MeshPart::getVertexArray() const {
            return this->impl->vertexArray;
        }
        */
        
        
        TypeInfo MeshPart::getTypeInfo() const {
            return TypeInfo::get<MeshPart>();
        }
        
        
        bool MeshPart::hasIndices() const {
            return true;
        }
    }
}
