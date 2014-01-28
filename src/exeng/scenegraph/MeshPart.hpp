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

namespace exeng { namespace scenegraph {

/**
 * @brief Three-Dimensional Model.
 */
class EXENGAPI MeshPart : public Object {
public:            
    MeshPart();
    
    virtual ~MeshPart();
    
    exeng::graphics::Primitive::Enum getPrimitiveType() const;
    
    void setPrimitiveType(exeng::graphics::Primitive::Enum primitiveType);
    
    const exeng::graphics::Material* getMaterial() const;
    
    void setMaterial(const exeng::graphics::Material* material);
    
    void setIndexBuffer( exeng::graphics::IndexBuffer *buffer);
    
    const exeng::graphics::IndexBuffer* getIndexBuffer() const;
    
    exeng::graphics::IndexBuffer* getIndexBuffer();
    
    void setVertexBuffer(exeng::graphics::VertexBuffer *buffer);
    
    const exeng::graphics::VertexBuffer* getVertexBuffer() const;
    
    exeng::graphics::VertexBuffer* getVertexBuffer();
    
    exeng::math::Boxf getBox() const;
    
    virtual TypeInfo getTypeInfo() const;
    
private:
    struct Private;
    Private *impl;
};
        
}}

#endif
