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

namespace exeng { namespace graphics { namespace gl3 {
///*
//	GL3VertexBuffer::GL3VertexBuffer(const VertexFormat &format, int count) {
//		this->allocate(format, count);
//	}
//
//	GL3VertexBuffer::~GL3VertexBuffer() {
//		this->release();
//	}
//
//	void GL3VertexBuffer::allocate(const VertexFormat &format, int count) {
//		int size = 0;
//        
//		this->release();
//
//		this->format = format;
//		this->count = count;
//
//		size = this->getSize();
//        
//		this->cacheBuffer.allocate(size);
//
//		{
//			BufferStatus<GL_ARRAY_BUFFER> status;
//            
//			::glGenVertexArrays(1, &this->vertexArrayId);
//			::glBindVertexArray(this->vertexArrayId);
//            
//			::glGenBuffers(1, &this->name); 
//			::glBindBuffer(GL_ARRAY_BUFFER, this->name); 
//			::glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
//            
//			::glBindVertexArray(0);
//            
//			GL3_CHECK();
//		}
//	}
//
//	void GL3VertexBuffer::release() {
//	#if defined(EXENG_DEBUG)
//		if (this->locked == true) {
//			throw std::runtime_error("GL3VertexBuffer::allocate: "
//									 "GL3VertexBuffer object is locked.");
//		}
//	#endif
//
//		if (this->name != 0) {
//			::glDeleteBuffers(1, &this->name);
//			this->name = 0;
//			GL3_CHECK();
//		}
//	}
//
//	bool GL3VertexBuffer::isEmpty() const {
//		return this->name == 0;
//	}
//
//
//	void* GL3VertexBuffer::lock() {
//	#if defined(EXENG_DEBUG)
//		if (this->locked == true) {
//			throw std::runtime_error("GL3VertexBuffer::lock: "
//									 "Buffer already locked");
//		}
//	#endif    
//		this->locked = true;
//		return this->buffer.getPtr();
//	}
//
//
//	bool GL3VertexBuffer::isLocked() const {
//		return this->locked;
//	}
//
//
//	void GL3VertexBuffer::unlock() {
//	#if defined(EXENG_DEBUG)
//		if (this->locked == false) {
//			throw std::runtime_error("The buffer isn't locked");
//		} else {
//	#endif
//			BufferStatus<GL_ARRAY_BUFFER> status;
//        
//			::glBindBuffer(GL_ARRAY_BUFFER, this->name);
//			::glBufferSubData(GL_ARRAY_BUFFER, 0, this->geSize(), this->buffer.getPtr());
//
//	#if defined(EXENG_DEBUG)
//		}
//	#endif
//    
//		this->locked = false;
//	}
//
//	int GL3VertexBuffer::getCount() const {
//		return this->count;
//	}
//
//	std::uint32_t GL3VertexBuffer::getSize() const {
//        return this->cacheBuffer.getSize();
//	}
//
//	const VertexFormat& GL3VertexBuffer::getFormat() const {
//		return this->format;
//	}
//
//	TypeInfo GL3VertexBuffer::getTypeInfo() const {
//		return TypeId<GL3VertexBuffer>();
//	}
//*/
}}}

// hola amorcito
