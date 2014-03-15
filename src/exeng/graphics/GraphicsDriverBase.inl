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
using namespace exeng::math;

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


    inline 
    VertexBuffer* 
    GraphicsDriverBase::createVertexBuffer( const VertexFormat &format, int count ) {
        auto *vbuffer = new HeapVertexBuffer(this, format, count);
//        this->addResource(vbuffer);
        return vbuffer;
    }


    inline 
    IndexBuffer* 
    GraphicsDriverBase::createIndexBuffer(IndexFormat indexFormat, int indexCount) {
        auto *indexBuffer = new HeapIndexBuffer(this);
        indexBuffer->allocate(indexFormat, indexCount);
//        this->addResource(indexBuffer);
        return indexBuffer;
    }


    inline void GraphicsDriverBase::setTransformName(Transform::Enum transform, const std::string &name) {
        this->transformNames[static_cast<int>(transform)] = name;
    }


    inline std::string GraphicsDriverBase::getTransformName(Transform::Enum transform) const {
        return this->transformNames[static_cast<int>(transform)];
    }

}}
