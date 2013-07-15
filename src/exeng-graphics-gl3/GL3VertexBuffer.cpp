/**
 * @file GL3VertexBuffer.cpp
 * @brief Implementation of the OpenGL 3 VertexBuffer class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "GL3GraphicsDriver.hpp"
#include "GL3VertexBuffer.hpp"
#include "GL3Debug.hpp"
#include "GL3BufferStatus.hpp"

#include <iostream>

namespace exeng {
namespace graphics {
namespace gl3 {

GL3VertexBuffer::GL3VertexBuffer(ResourceFactory *factory, 
                                 const VertexFormat &format, 
                                 int count) : VertexBuffer(factory) {
    this->vertexArrayId = 0;
    this->name = 0;
    this->locked = false;
    
    this->allocate(format, count);
}


GL3VertexBuffer::~GL3VertexBuffer() {
    this->release();
}


void GL3VertexBuffer::allocate(const VertexFormat &format, int count) {
    if (this->locked == true) {
        const char *msg = "GL3VertexBuffer::allocate: "
                          "GL3VertexBuffer object is locked.";
        throw std::runtime_error(msg);
    } else {
        int size = 0;
        
        this->release();
        
        this->format = format;
        this->count = count;
        
        size = this->getSize();
        
        this->buffer.allocate(size);
        {
            BufferStatus<GL_ARRAY_BUFFER> status;
            
            ::glGenVertexArrays(1, &this->vertexArrayId);
            ::glBindVertexArray(this->vertexArrayId);
            
            ::glGenBuffers(1, &this->name); 
            ::glBindBuffer(GL_ARRAY_BUFFER, this->name); 
            ::glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
            
            ::glBindVertexArray(0);
            
            GL3_CHECK();
        }
    }
}


void GL3VertexBuffer::release() {
    if (this->locked == true) {
        throw std::runtime_error("GL3VertexBuffer::allocate: "
                                 "GL3VertexBuffer object is locked.");
    } else {
        if (this->name != 0) {
            ::glDeleteBuffers(1, &this->name);
            this->name = 0;
            GL3_CHECK();
        }
    }
}


bool GL3VertexBuffer::isEmpty() const {
    return this->name == 0;
}


void* GL3VertexBuffer::lock() {
    if (this->locked == true) {
        throw std::runtime_error("GL3VertexBuffer::lock: "
                                 "Buffer already locked");
    }
    
    this->locked = true;
    return this->buffer.getPtr();
}


bool GL3VertexBuffer::isLocked() const {
    return this->locked;
}


void GL3VertexBuffer::unlock() {
    if (this->locked == false) {
        throw std::runtime_error("The buffer isn't locked");
    } else {
        BufferStatus<GL_ARRAY_BUFFER> status;
        
        ::glBindBuffer(GL_ARRAY_BUFFER, this->name);
        ::glBufferSubData(GL_ARRAY_BUFFER, 0, this->getSize(), this->buffer.getPtr());
    }
    
    this->locked = false;
}


int GL3VertexBuffer::getCount() const {
    return this->count;
}


int GL3VertexBuffer::getSize() const {
    return this->count * this->format.getSize();
}


const VertexFormat& GL3VertexBuffer::getFormat() const {
    return this->format;
}
}
}
}

// hola amorcito
