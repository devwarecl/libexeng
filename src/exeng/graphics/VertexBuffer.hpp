/**
 * @brief
 */

#ifndef __EXENG_GRAPHICS_VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_VERTEXBUFFER_HPP__

#include "../Object.hpp"
#include "VertexBufferFormat.hpp"

namespace exeng
{
    namespace graphics
    {
        /**
         * @brief Graphics driver specific 
         */
        class EXENGAPI VertexBuffer : public Object
        {
        public:
            
            /**
             * @brief
             */
            virtual ~VertexBuffer() {}
            
            /**
             * @brief Lock the vertex and get a raw pointer to the vertex data, enabling high-performance manipulation o data retrieval. 
             * A locked vertex buffer can't be used for rendering operations
             */
            virtual void* lock() = 0;
            
            /**
             * @brief Unlock the vertex buffer, making it valid for rendering operations. 
             * The previously returned buffer isn't valid anymore.
             */
            virtual void unlock() = 0;
            
            /**
             * @brief Get the vertex format descriptor. 
             */
            virtual VertexBufferFormat getFormat() const = 0;
            
            /**
             * @brief Get total number of vertices holded by this vertex buffer.
             */
            virtual int getCount() const = 0;
        };
    }
}

#endif
