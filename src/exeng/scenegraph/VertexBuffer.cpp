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
#include "VertexBuffer.hpp"
#include <boost/checked_delete.hpp>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace exeng {
    namespace scenegraph {
        
        struct VertexBuffer::Private {
            HeapBuffer buffer;
            
            /**
             * @brief Numero de vertices que almacena este buffer
             */
            int count;
            
            /**
             * @brief Tamaño, en bytes, de cada vertice, dentro del buffer de vertices
             */
            int size;
            
            Private() : count(0), size(0) {}
            ~Private() { }
        };
        
        
        VertexBuffer::VertexBuffer() : impl(new VertexBuffer::Private()) {
        }
        
        
        VertexBuffer::VertexBuffer(int vertexSize, int vertexCount) : impl(new VertexBuffer::Private())  {
            this->allocate(vertexSize, vertexCount);
        }
        
        
        VertexBuffer::~VertexBuffer() {   
            boost::checked_delete(this->impl);
        }
        
        
        void VertexBuffer::allocate(int vertexSize, int vertexCount)  {
            assert(this->impl != nullptr);
            
            this->impl->buffer.allocate(vertexSize * vertexCount);
            this->impl->count = vertexCount;
        }
         
        
        void VertexBuffer::release() {
            assert(this->impl != nullptr);
            
            this->impl->buffer.release();
        }
        
        
        bool VertexBuffer::isEmpty() const {   
            assert(this->impl != nullptr);
            return this->isEmpty();
        }
        
        
        void* VertexBuffer::lock() {
            assert(this->impl != nullptr);

            return this->impl->buffer.lock();
        }
        
        
        bool VertexBuffer::isLocked() const {
            assert(this->impl != nullptr);
            
            return this->impl->buffer.isLocked();
        }
        
        
        void VertexBuffer::unlock() {
            assert(this->impl != nullptr);
            
            this->unlock();
        }
        

        int VertexBuffer::getCount() const {
            assert(this->impl != nullptr);
            
            return this->impl->count;
        }
        
        
        int VertexBuffer::getSize() const {
            assert(this->impl != nullptr);
            
            return this->impl->size;
        }
    }
}
