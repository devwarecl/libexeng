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

#include <cassert>
#include <boost/range/algorithm/find_if.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/HeapBuffer.hpp>

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

    inline Buffer* GraphicsDriverBase::createVertexBuffer(const std::int32_t size, const void* data)  {
        Buffer *buffer = new HeapBuffer(size);

        if (data) {
            buffer->setData(data, size);
        }

        return buffer;
    }

    inline Buffer* GraphicsDriverBase::createIndexBuffer(const std::int32_t size, const void* data) {
        Buffer *buffer = new HeapBuffer(size);

        if (data) {
            buffer->setData(data, size);
        }

        return buffer;
    }

    inline void GraphicsDriverBase::setTransformName(Transform::Enum transform, const std::string &name) {
        this->transformNames[static_cast<int>(transform)] = name;
    }

    inline std::string GraphicsDriverBase::getTransformName(Transform::Enum transform) const {
        return this->transformNames[static_cast<int>(transform)];
    }
}}
