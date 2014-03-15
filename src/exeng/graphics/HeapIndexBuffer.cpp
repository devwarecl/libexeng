/**
 * @file HeapIndexBuffer.cpp
 * @brief Implementation for class HeapIndexBuffer
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/graphics/HeapIndexBuffer.hpp>

#include <cstdlib>
#include <stdexcept>
#include <cassert>
#include <boost/checked_delete.hpp>
#include <exeng/HeapBuffer.hpp>

namespace exeng {
    namespace graphics {
        
        struct HeapIndexBuffer::Private {
            HeapBuffer buffer;
            int count;
            IndexFormat format;
            
            Private() : count(0) {}
            ~Private() {}
        };
        
        
        HeapIndexBuffer::HeapIndexBuffer(ResourceManager *factory) : 
            IndexBuffer(factory), impl(nullptr) {
            this->impl = new HeapIndexBuffer::Private();
        }
        
        
        HeapIndexBuffer::HeapIndexBuffer(ResourceManager *factory, IndexFormat indexFormat, int indexCount) : 
            IndexBuffer(factory), impl(nullptr)  {
            this->impl = new HeapIndexBuffer::Private();
            this->allocate(indexFormat, indexCount);
        }
        
        
        HeapIndexBuffer::~HeapIndexBuffer() {   
            boost::checked_delete(this->impl);
        }
        
        
        void HeapIndexBuffer::allocate(IndexFormat indexFormat, int indexCount)  {
            assert(this->impl != nullptr);
            
            int indexSize = static_cast<int>(indexFormat);
            
            this->impl->buffer.allocate(indexSize * indexCount);
            this->impl->format = indexFormat;
            this->impl->count = indexCount;
        }
         
        
        void HeapIndexBuffer::release() {
            assert(this->impl != nullptr);
            this->impl->buffer.release();
        }
        
        
        bool HeapIndexBuffer::isEmpty() const {   
            assert(this->impl != nullptr);
            return this->impl->buffer.isEmpty();
        }
        
        
        void* HeapIndexBuffer::lock() {
            assert(this->impl != nullptr);
            return this->impl->buffer.lock();
        }
        
        
        bool HeapIndexBuffer::isLocked() const {
            assert(this->impl != nullptr);
            return this->impl->buffer.isLocked();
        }
        
        
        void HeapIndexBuffer::unlock() {
            assert(this->impl != nullptr);
            this->impl->buffer.unlock();
        }
        

        int HeapIndexBuffer::getCount() const {
            assert(this->impl != nullptr);
            return this->impl->count;
        }
        
        
        IndexFormat HeapIndexBuffer::getFormat() const {
            assert(this->impl != nullptr);
            return this->impl->format;
        }
    }
}
