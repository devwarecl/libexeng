
/**
 * @brief Implementacion trivial de los buffers de vertices
 */

#include "VertexBuffer.hpp"
#include <boost/checked_delete.hpp>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace exeng {
    namespace scenegraph {
        
        const char errLockedBuffer[] = "The buffer is locked";
        const char errUnlockedBuffer[] = "The buffer is unlocked";
        
        struct VertexBuffer::Private {
            void* data;
            bool locked;
            int size;
            int count;
            
            Private() : data(nullptr), locked(false), size(0), count(0) {}
            
            
            ~Private() {
                this->release();
            }
        
            
            void allocate(int size) {
                this->data = std::malloc(size);
            }
            
            
            void release() {
                std::free(this->data);
                this->data = nullptr;
            }
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
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            this->impl->allocate(vertexSize * vertexCount);
            this->impl->size = vertexSize;
            this->impl->count = vertexCount;
        }
         
        
        void VertexBuffer::release() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            this->impl->release();
        }
        
        
        bool VertexBuffer::isEmpty() const {   
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            if (this->impl->data != nullptr) {
                return false;
            } else {
                return true;
            }
        }
        
        
        void* VertexBuffer::lock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            this->impl->locked = true;
            
            return this->impl->data;
        }
        
        
        bool VertexBuffer::tryLock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                return false;
            } else {
                return true;
            }
        }
        
        void VertexBuffer::unlock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == false) {
                throw std::runtime_error(errUnlockedBuffer);
            }
            
            this->impl->locked = false;
        }
        

        int VertexBuffer::getCount() const {
            return this->impl->count;
        }
        
        
        int VertexBuffer::getSize() const {
            return this->impl->size;
        }
    }
}
