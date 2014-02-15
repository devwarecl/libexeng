/**
 * @file GraphicsDriverBase.hpp
 * @brief Defines the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include <exeng/graphics/GraphicsDriver.hpp>

#include <list>
#include <boost/shared_ptr.hpp>

namespace exeng { namespace graphics {

/**
 * @brief Base common functionality for easing the process 
 * of implementing graphics drivers
 */
class GraphicsDriverBase : public GraphicsDriver {
public:
    GraphicsDriverBase();
    
    virtual ~GraphicsDriverBase();
    
    virtual exeng::math::Matrix4f getTransform( Transform::Enum transform );
    
    virtual exeng::math::Rectf getViewport( ) const;
    
    virtual const exeng::graphics::Material* getMaterial( ) const;
    
    virtual VertexBuffer* createVertexBuffer( const VertexFormat &vertexFormat, int vertexCount );
    
    virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, int IndexCount );
    
    virtual void setTransformName(Transform::Enum transform, const std::string &name);
    
    virtual std::string getTransformName(Transform::Enum transform) const;
    
protected:
    const exeng::graphics::Material* material;
    exeng::math::Rectf viewport;
    exeng::math::Matrix4f transforms[3];
    std::string transformNames[3];
};

}}

#include "GraphicsDriverBase.inl"

#endif  // __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
