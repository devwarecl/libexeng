
#ifndef __EXENG_GRAPHICS_MESHSUBSET_HPP__
#define __EXENG_GRAPHICS_MESHSUBSET_HPP__

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/Primitive.hpp>

namespace exeng { namespace graphics {
    class EXENGAPI MeshSubset : public Object {
    public:
        MeshSubset(const std::vector<VertexBuffer*> &vertexBuffers, IndexBuffer *indexBuffer);

        virtual ~MeshSubset();

        virtual int getVertexBufferCount() const = 0;
        virtual VertexBuffer* getVertexBuffer(const int index) = 0;
        virtual const VertexBuffer* getVertexBuffer(const int index) const = 0;

        virtual IndexBuffer* getIndexBuffer() = 0;
        virtual const IndexBuffer* getIndexBuffer() const = 0;

    private:
        struct Private;
        Private *impl;
    };
}}

#endif  // __EXENG_GRAPHICS_MESHSUBSET_HPP__
