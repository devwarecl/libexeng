

/**
 * @file IndexArray.hpp
 * @brief Defines the IndexArray class template.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_INDEXARRAY_HPP__
#define __EXENG_GRAPHICS_INDEXARRAY_HPP__

#include <cassert>
#include <stdexcept>
#include <exeng/Config.hpp>

namespace exeng {
    namespace graphics {
        
        class EXENGAPI IndexBuffer;
        
        /**
         * @brief Help to initialize values of a object of type IndexBuffer.
         */
        template<typename IndexType>
        class IndexArray {
        public:
            
            IndexArray(IndexBuffer *buffer) {
                this->bufferData = static_cast<IndexType*>(buffer->lock());
                this->buffer = buffer;
            }
            
            
            ~IndexArray() {
                this->buffer->unlock();
            }
            
            
            IndexType& operator[] (int index) {
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range();
                }
                
                return this->bufferData[index];
            }
            
            
            const IndexType& operator[] (int index) const {
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range();
                }
                
                return this->bufferData[index];
            }
            
            
            int size() const {
                return this->buffer->getCount();
            }
            
            
        private:
            IndexBuffer *buffer;
            IndexType *bufferData;
        };
    }
}

#endif