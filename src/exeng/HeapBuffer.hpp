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

#ifndef exeng_heapbuffer_hpp
#define exeng_heapbuffer_hpp

#include <exeng/Buffer.hpp>

namespace exeng {
    /**
     * @brief Raw memory allocated in the heap.
     */
    class EXENGAPI HeapBuffer : public Buffer {
    public:
        HeapBuffer();
    
        explicit HeapBuffer(int size);
        
        virtual ~HeapBuffer();
        
        virtual void* lock();
        
        virtual void unlock();
        
        virtual const void* lock() const;
        
        virtual void unlock() const;
        
        virtual bool isLocked() const;
        
        virtual bool isEmpty() const;
        
        virtual int getSize() const;
        
        /**
         * @brief Change the size of the buffer.
         * @param size The new size of the current buffer, in bytes.
         */
        void allocate(int size);
        
        /**
         * @brief Free the allocated memory.
         */
        void release();
        
        /**
         * @brief Get a pointer to the buffer data
         */
        void* getPtr();
        const void* getPtr() const;
        
    private:
        void* data;				//! The buffer raw data.
        int size;				//! The size of the buffer, in bytes.
        mutable bool locked;	//! Lock status.
    };
}

#endif // exeng_heapbuffer_hpp
