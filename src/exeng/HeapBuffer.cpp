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


#include "HeapBuffer.hpp"

namespace exeng {
    const char errLockedBuffer[] = "The buffer is locked";
    const char errUnlockedBuffer[] = "The buffer is unlocked";

    HeapBuffer::HeapBuffer() : data(nullptr), size(0), locked(false) {
    }
    
    
    HeapBuffer::HeapBuffer(int size) : data(nullptr), size(0), locked(false) {
        this->allocate(size);
    }
    
    
    HeapBuffer::~HeapBuffer() {
        this->release();
    }
    
    
    void* HeapBuffer::lock() {
#ifdef EXENG_DEBUG
        if (this->locked == true) {
            throw std::runtime_error(errLockedBuffer);
        }
        
        if (this->isEmpty() == true) {
            throw std::runtime_error("The buffer must not be empty");
        }
#endif
        this->locked = true;
        return this->data;
        
    }
    
    
    void HeapBuffer::unlock() {
#ifdef EXENG_DEBUG
        if (this->locked == false) {
            throw std::runtime_error(errUnlockedBuffer);
        }
#endif
        this->locked = false;
    }
    
    
    const void* HeapBuffer::lock() const {
#ifdef EXENG_DEBUG
        if (this->locked == true) {
            throw std::runtime_error(errLockedBuffer);
        }
        
        if (this->isEmpty() == true) {
            throw std::runtime_error("The buffer must not be empty");
        }
#endif
        this->locked = true;
        return this->data;
    }
    
    
    void HeapBuffer::unlock() const {
#ifdef EXENG_DEBUG
        if (this->locked == false) {
            throw std::runtime_error(errUnlockedBuffer);
        }
#endif
        this->locked = false;
    }
    
    
    bool HeapBuffer::isLocked() const {
        return this->locked;
    }
    
    
    bool HeapBuffer::isEmpty() const {
        return this->size != 0;   
    }

    
    void HeapBuffer::allocate(int size) {
#ifdef EXENG_DEBUG
        if (this->locked == true) {
            throw std::runtime_error(errLockedBuffer);
        }
#endif
        this->release();      
        this->data = std::malloc(size);
        this->size = size;
    }
    
    
    void HeapBuffer::release() {
#ifdef EXENG_DEBUG
        if (this->locked == true) {
            //! TODO: Append to the log a warning for deleting a locked resource.
        }
#endif
        
        if (this->data != nullptr) {
            std::free(this->data);
            
            this->data = nullptr;
            this->size = 0;
        }
    }
    
    
    int HeapBuffer::getSize() const {
        return this->size;
    }
}
