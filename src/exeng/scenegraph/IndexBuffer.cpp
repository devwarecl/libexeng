
/**
 * @brief Implementacion trivial de los buffers de indices
 */

#include "IndexBuffer.hpp"
#include <boost/checked_delete.hpp>
#include <cstdlib>
#include <stdexcept>
#include <cassert>

namespace exeng {
    namespace scenegraph {
        
        const char errLockedBuffer[] = "The buffer is locked";
        const char errUnlockedBuffer[] = "The buffer is unlocked";
        
        struct IndexBuffer::Private {
            void* data;
            bool locked;
            IndexFormat format;
            int count;
            
            Private() : data(nullptr), locked(false), count(0) {}
            
            
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
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            int indexSize = static_cast<int>(indexFormat);
            
            this->impl->allocate(indexSize * indexCount);
            this->impl->format = indexFormat;
            this->impl->count = indexCount;
        }
         
        
        void IndexBuffer::release() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            this->impl->release();
        }
        
        
        bool IndexBuffer::isEmpty() const {   
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
        
        
        void* IndexBuffer::lock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                throw std::runtime_error(errLockedBuffer);
            }
            
            this->impl->locked = true;
            
            return this->impl->data;
        }
        
        
        bool IndexBuffer::tryLock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == true) {
                return false;
            } else {
                return true;
            }
        }
        
        void IndexBuffer::unlock() {
            assert(this->impl != nullptr);
            
            if (this->impl->locked == false) {
                throw std::runtime_error(errUnlockedBuffer);
            }
            
            this->impl->locked = false;
        }
        

        int IndexBuffer::getCount() const {
            return this->impl->count;
        }
        
        
        IndexFormat IndexBuffer::getFormat() const {
            return this->impl->format;
        }
    }
}
