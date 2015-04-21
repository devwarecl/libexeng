
#ifndef __EXENG_GRAPHICS_IBUFFERFACTORY_HPP__
#define __EXENG_GRAPHICS_IBUFFERFACTORY_HPP__

#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/IndexBuffer.hpp>

namespace exeng { namespace graphics {
    class EXENGAPI IBufferFactory {
    public:
        virtual ~IBufferFactory();
        // virtual VertexBuffer* createVertexBuffer();
        // virtual IndexBuffer* createIndexBuffer();
    };
}}

#endif  
