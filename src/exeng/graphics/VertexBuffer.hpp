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


#ifndef __EXENG_GRAPHICS_VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_VERTEXBUFFER_HPP__

#include <stdexcept>

#include <exeng/Resource.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics {

/**
 *  @brief Simple vertex structure. 
 */
struct Vertex {
    exeng::math::Vector3f coord;
    exeng::math::Vector3f normal;
    exeng::math::Vector2f texCoord;
};

/**
 * @brief Buffer that stores vertex data, directly in VideoRAM.
 */
class EXENGAPI VertexBuffer : public Resource {
public:
    VertexBuffer(ResourceFactory *resourceFactory);
    
    virtual ~VertexBuffer();
    
    /**
     * @brief Allocate memory to store a set of vertices.
     */
    virtual void allocate(const VertexFormat &format, int count) = 0;
    
    /**
     * @brief Frees the memory allocated by the vertex buffer, 
     * making it empty.
     */
    virtual void release() = 0;
    
    /**
     * @brief Check if the buffer is empty.
     */
    virtual bool isEmpty() const = 0;
    
    /**
     * @brief Locks the buffer. Throws exception if already locked.
     */
    virtual void* lock() = 0;
    
    /**
     * @brief Check if the vertex buffer is locked.
     */
    virtual bool isLocked() const = 0;
    
    /**
     * @brief Unlocks the vertex buffer.
     */
    virtual void unlock() = 0;
    
    /**
     * @brief Get the count of vertices stored in the vertex buffer.
     */
    virtual int getCount() const = 0;
    
    /**
     * @brief Get the total allocated size for the vertex buffer
     */
    virtual int getSize() const = 0;
    
    /**
     * @brief Get the current vertex format
     */
    virtual const VertexFormat& getFormat() const = 0;
};
    
}}

#endif  //__EXENG_GRAPHICS_VERTEXBUFFER_HPP__
