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


#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/VertexArray.hpp>
#include <exeng/scenegraph/MeshPart.hpp>
#include <boost/checked_delete.hpp>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::math;

namespace exeng { namespace scenegraph {

struct MeshPart::Private {
    const Material *material;
    VertexBuffer *vertexBuffer;
    IndexBuffer *indexBuffer;
    exeng::graphics::Primitive::Enum primitiveType;
    
    Private() : material(nullptr), vertexBuffer(nullptr), indexBuffer(nullptr) {
        this->primitiveType = exeng::graphics::Primitive::Enum::TriangleList;
    }
};


MeshPart::MeshPart() : impl(new MeshPart::Private()) {
}


MeshPart::~MeshPart() {
    boost::checked_delete(this->impl);
}


exeng::graphics::Primitive::Enum MeshPart::getPrimitiveType() const {
    assert(this->impl != nullptr);
    
    return this->impl->primitiveType;
}


void MeshPart::setPrimitiveType(exeng::graphics::Primitive::Enum primitiveType) {
    assert(this->impl != nullptr);
    
    this->impl->primitiveType = primitiveType;
}


const Material* MeshPart::getMaterial() const {
    assert(this->impl != nullptr);
    
    return this->impl->material;
}


void MeshPart::setMaterial(const Material* material) {
    assert(this->impl != nullptr);
    
    this->impl->material = material;
}


void MeshPart::setIndexBuffer(IndexBuffer *buffer) {
    assert(this->impl != nullptr);
    
    this->impl->indexBuffer = buffer;
}


const IndexBuffer* MeshPart::getIndexBuffer() const {
    assert(this->impl != nullptr);
    
    return this->impl->indexBuffer;
}


IndexBuffer* MeshPart::getIndexBuffer() {
    assert(this->impl != nullptr);
    
    return this->impl->indexBuffer;
}


void MeshPart::setVertexBuffer(VertexBuffer *buffer) {
    assert(this->impl != nullptr);
    
    this->impl->vertexBuffer = buffer;
}


const VertexBuffer* MeshPart::getVertexBuffer() const {
    assert(this->impl != nullptr);
    
    return this->impl->vertexBuffer;
}


VertexBuffer* MeshPart::getVertexBuffer(){
    assert(this->impl != nullptr);
    
    return this->impl->vertexBuffer;
}


TypeInfo MeshPart::getTypeInfo() const {
    assert(this->impl != nullptr);
    
    return TypeId<MeshPart>();
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


}}
