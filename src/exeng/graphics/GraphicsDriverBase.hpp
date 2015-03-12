/**
 * @file GraphicsDriverBase.hpp
 * @brief Defines the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/HeapBuffer.hpp>
#include <list>
#include <memory>

namespace exeng { namespace graphics {
    /**
     * @brief Base common functionality for easing the process 
     * of implementing graphics drivers
     */
    class GraphicsDriverBase : public GraphicsDriver {
    public:
        GraphicsDriverBase();
        virtual ~GraphicsDriverBase();
        virtual exeng::Rectf getViewport() const override;
        virtual const exeng::graphics::Material* getMaterial() const override;
        virtual std::unique_ptr<Buffer> createVertexBuffer(const std::int32_t size, const void* data) override;
        virtual std::unique_ptr<Buffer> createIndexBuffer(const std::int32_t size, const void* data) override;

    protected:
        const Material *material = nullptr;
        Rectf viewport;
    };


	inline GraphicsDriverBase::GraphicsDriverBase() {
        this->viewport.set(0.0f);
        this->material = nullptr;
    }

    inline GraphicsDriverBase::~GraphicsDriverBase() {}
    
    inline const Material* GraphicsDriverBase::getMaterial() const {
        return this->material;
    }

    inline Rectf GraphicsDriverBase::getViewport() const {
        return this->viewport;
    }

    inline std::unique_ptr<Buffer> GraphicsDriverBase::createVertexBuffer(const std::int32_t size, const void* data)  {
        auto buffer = std::unique_ptr<Buffer>(new HeapBuffer(size));

        if (data) {
            buffer->setData(data, size);
        }

        return buffer;
    }

    inline std::unique_ptr<Buffer> GraphicsDriverBase::createIndexBuffer(const std::int32_t size, const void* data) {
        auto buffer = std::unique_ptr<Buffer>(new HeapBuffer(size));

        if (data) {
            buffer->setData(data, size);
        }

        return buffer;
    }
}}

#endif  // __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
