
/**
 * @file VertexArray.hpp
 * @brief Defines the VertexArray template.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_VERTEXARRAY_HPP__
#define __EXENG_GRAPHICS_VERTEXARRAY_HPP__

#include <cassert>
#include <stdexcept>
#include <exeng/Config.hpp>
#include <exeng/graphics/VertexBuffer.hpp>

namespace exeng { namespace graphics {

    class EXENGAPI VertexBuffer;
            
    /**
     * @brief Help to the initialization of vertex buffers by user code.
     */
    template<typename VertexType>
    class VertexArray {
    public:
        VertexArray(VertexBuffer *buffer) : buffer(nullptr), bufferData(nullptr) {
    #ifdef EXENG_DEBUG
            if (buffer == nullptr) {
                throw std::runtime_error("VertexArray::VertexArray: The buffer can't be null");
            }
    
            if (buffer->getFormat().getSize() != sizeof(VertexType)) {
                throw std::runtime_error("VertexArray::VertexArray: Invalid supplied VertexType: must be equal to the size reported by the vertexBuffer's format.");
            }
    #endif
            this->bufferData = static_cast<VertexType*>(buffer->lock());
            this->buffer = buffer;
        }
        
        ~VertexArray() {
            this->buffer->unlock();
        }
        
        VertexType& operator[] (int index) {          
    #ifdef EXENG_DEBUG
            if (index >= this->buffer->getCount()) {
                throw std::out_of_range("");
            }
    #endif
            return this->bufferData[index];
        }
        
        const VertexType& operator[] (int index) const {
    #ifdef EXENG_DEBUG
            if (index >= this->buffer->getCount()) {
                throw std::out_of_range("");
            }
    #endif                
            return this->bufferData[index];
        }
        
        int size() const {
            return this->buffer->getCount();
        }
    private:
        VertexBuffer *buffer;
        VertexType *bufferData;
    };
}}


#endif  //__EXENG_GRAPHICS_VERTEXARRAY_HPP__

