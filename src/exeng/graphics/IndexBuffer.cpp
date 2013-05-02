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

#include "../HeapBuffer.hpp"
#include "IndexBuffer.hpp"
#include <boost/checked_delete.hpp>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace exeng {
    namespace graphics {
        
        struct IndexBuffer::Private {
            HeapBuffer buffer;
            int count;
            IndexFormat format;
            
            Private() : count(0) {}
            ~Private() { }
        };
        
        
        IndexBuffer::IndexBuffer() : impl(new IndexBuffer::Private()) {
        }
        
        
        IndexBuffer::IndexBuffer(IndexFormat indexFormat, int indexCount) : impl(new IndexBuffer::Private())  {
            this->allocate(indexFormat, indexCount);
        }
        
        
        IndexBuffer::~IndexBuffer() {   
            boost::checked_delete(this->impl);
        }
        
        
        void IndexBuffer::allocate(IndexFormat indexFormat, int indexCount)  {
            assert(this->impl != nullptr);
            
            int indexSize = static_cast<int>(indexFormat);
            
            this->impl->buffer.allocate(indexSize * indexCount);
            this->impl->format = indexFormat;
            this->impl->count = indexCount;
        }
         
        
        void IndexBuffer::release() {
            assert(this->impl != nullptr);

            this->impl->buffer.release();
        }
        
        
        bool IndexBuffer::isEmpty() const {   
            assert(this->impl != nullptr);
            
            return this->impl->buffer.isEmpty();
        }
        
        
        void* IndexBuffer::lock() {
            assert(this->impl != nullptr);
            
            return this->impl->buffer.lock();
        }
        
        
        bool IndexBuffer::isLocked() const {
            assert(this->impl != nullptr);
            
            return this->impl->buffer.isLocked();
        }
        
        void IndexBuffer::unlock() {
            assert(this->impl != nullptr);
            
            this->impl->buffer.unlock();
        }
        

        int IndexBuffer::getCount() const {
            assert(this->impl != nullptr);
            return this->impl->count;
        }
        
        
        IndexFormat IndexBuffer::getFormat() const {
            assert(this->impl != nullptr);
            return this->impl->format;
        }
    }
}
