
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
#include <exeng/Buffer.hpp>

namespace exeng { namespace graphics {

    // class EXENGAPI VertexBuffer;
            
    /**
     * @brief Help to the initialization of vertex buffers by user code.
     */
    template<typename VertexType>
    class VertexArray {
    public:
        VertexArray(Buffer *buffer_) : buffer(nullptr), bufferData(nullptr) {
    #ifdef EXENG_DEBUG
            if (buffer_ == nullptr) {
                throw std::runtime_error("VertexArray::VertexArray: The buffer can't be null");
            }
    
            if (buffer_->getFormat().geSize() != sizeof(VertexType)) {
                throw std::runtime_error("VertexArray::VertexArray: Invalid supplied VertexType: must be equal to the size reported by the vertexBuffer's format.");
            }
    #endif
            this->buffer = buffer_;
            this->bufferData = static_cast<VertexType*>(this->buffer->getDataPtr());
        }
        
        ~VertexArray() {
            this->buffer->write();
        }
        
        VertexType& operator[] (int index) {          
            return this->bufferData[index];
        }
        
        const VertexType& operator[] (int index) const {
            return this->bufferData[index];
        }

    private:
        Buffer *buffer;
        VertexType *bufferData;
    };
}}


#endif  //__EXENG_GRAPHICS_VERTEXARRAY_HPP__

