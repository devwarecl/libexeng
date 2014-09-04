/**
 * @file GraphicsDriverBase.cpp
 * @brief Implementation of the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <exeng/graphics/GraphicsDriverBase.hpp>

#include <cassert>
#include <boost/range/algorithm/find_if.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/graphics/VertexBuffer.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/HeapVertexBuffer.hpp>
#include <exeng/graphics/HeapIndexBuffer.hpp>

using namespace exeng;
using namespace exeng::graphics;

namespace exeng { namespace graphics {

    inline GraphicsDriverBase::GraphicsDriverBase() {
        this->viewport.set(0.0f);
        this->material = nullptr;
    }

    inline GraphicsDriverBase::~GraphicsDriverBase() {}
    
    inline Matrix4f GraphicsDriverBase::getTransform(Transform::Enum transform) {
        return this->transforms[static_cast<const int>(transform)];
    }

    inline const Material* GraphicsDriverBase::getMaterial() const {
        return this->material;
    }

    inline Rectf GraphicsDriverBase::getViewport() const {
        return this->viewport;
    }

    inline VertexBuffer* GraphicsDriverBase::createVertexBuffer( const VertexFormat &format, int count, const void *data)  {
        VertexBuffer *vertexBuffer = new HeapVertexBuffer(this, format, count);

        if (data) {
            void* destPtr = vertexBuffer->lock();
            std::memcpy(destPtr, data, count * format.geSize());
            vertexBuffer->unlock();
        }

        return vertexBuffer;
    }

    inline IndexBuffer* GraphicsDriverBase::createIndexBuffer(IndexFormat::Enum indexFormat, int indexCount, const void *data) {
        IndexBuffer *indexBuffer = new HeapIndexBuffer(this);
        indexBuffer->allocate(indexFormat, indexCount);

        if (data) {
            void* destPtr = indexBuffer->lock();
            std::memcpy(destPtr, data, indexCount * IndexFormat::geSize(indexFormat));
            indexBuffer->unlock();
        }

        return indexBuffer;
    }

    inline void GraphicsDriverBase::setTransformName(Transform::Enum transform, const std::string &name) {
        this->transformNames[static_cast<int>(transform)] = name;
    }

    inline std::string GraphicsDriverBase::getTransformName(Transform::Enum transform) const {
        return this->transformNames[static_cast<int>(transform)];
    }
}}
