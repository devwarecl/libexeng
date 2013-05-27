/**
 * @file HeapVertexBuffer.hpp
 * @brief Implementation of the HeapVertexBuffer class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <exeng/graphics/HeapVertexBuffer.hpp>

#include <cassert>
#include <stdexcept>
#include <boost/checked_delete.hpp>
#include <exeng/HeapBuffer.hpp>

namespace exeng {
    namespace graphics {
        struct HeapVertexBuffer::Private {
        public:
            Private() : count(0) {}
            ~Private() { }
        
        public:
            int count;              //! Number of vertices 
            VertexFormat format;    //! The vertex format of the vertex buffer.
            HeapBuffer buffer;      //! The buffer storing the data.
        };
        
        
        HeapVertexBuffer::HeapVertexBuffer() : impl(nullptr) {
            this->impl = new HeapVertexBuffer::Private();
        }
        
        
        HeapVertexBuffer::HeapVertexBuffer(const VertexFormat &format, int count) : impl(nullptr) {
            this->impl = new HeapVertexBuffer::Private();
            this->allocate(format, count);
        }
        
        
        HeapVertexBuffer::~HeapVertexBuffer() {   
            boost::checked_delete(this->impl);
        }
        
        
        void HeapVertexBuffer::allocate(const VertexFormat &format, int count)  {
            assert(this->impl != nullptr);
            this->impl->buffer.allocate(format.getSize() * count);
            this->impl->count = count;
            this->impl->format = format;
        }
        
        
        void HeapVertexBuffer::release() {
            assert(this->impl != nullptr);
            this->impl->buffer.release();
        }
        
        
        bool HeapVertexBuffer::isEmpty() const {   
            assert(this->impl != nullptr);
            return this->isEmpty();
        }
        
        
        void* HeapVertexBuffer::lock() {
            assert(this->impl != nullptr);
            return this->impl->buffer.lock();
        }
        
        
        bool HeapVertexBuffer::isLocked() const {
            assert(this->impl != nullptr);
            return this->impl->buffer.isLocked();
        }
        
        
        void HeapVertexBuffer::unlock() {
            assert(this->impl != nullptr);
            this->unlock();
        }
        
        
        int HeapVertexBuffer::getCount() const {
            assert(this->impl != nullptr);
            return this->impl->count;
        }
        
        
        int HeapVertexBuffer::getSize() const {
            assert(this->impl != nullptr);
            return this->getCount() * this->getFormat().getSize();
        }
        
        const VertexFormat& HeapVertexBuffer::getFormat() const {
            assert(this->impl != nullptr);
            return this->impl->format;
        }
    }
}
