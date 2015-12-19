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

#include <memory>
#include <list>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/HeapBuffer.hpp>

namespace xe { namespace gfx {
    /**
     * @brief Base common functionality for easing the process 
     * of implementing graphics drivers
     */
    class GraphicsDriverBase : public GraphicsDriver {
    public:
		GraphicsDriverBase();
		virtual ~GraphicsDriverBase() {}
        virtual xe::Rectf getViewport() const override;
        virtual const xe::gfx::Material* getMaterial() const override;
        virtual BufferPtr createVertexBuffer(const std::int32_t size, const void* data) override;
        virtual BufferPtr createIndexBuffer(const std::int32_t size, const void* data) override;

		virtual ModernModule* getModernModule() override;

		virtual LegacyModule* getLegacyModule() override;

    protected:
        const Material *material = nullptr;
        Rectf viewport;
    };


	inline GraphicsDriverBase::GraphicsDriverBase() {
        this->viewport.set(0.0f);
    }

    inline const Material* GraphicsDriverBase::getMaterial() const {
        return this->material;
    }

    inline Rectf GraphicsDriverBase::getViewport() const {
        return this->viewport;
    }

    inline std::unique_ptr<Buffer> GraphicsDriverBase::createVertexBuffer(const std::int32_t size, const void* data)  {
        auto buffer = std::unique_ptr<Buffer>(new HeapBuffer(size));

        if (data) {
            buffer->setData(data);
        }

        return buffer;
    }

    inline std::unique_ptr<Buffer> GraphicsDriverBase::createIndexBuffer(const std::int32_t size, const void* data) {
        auto buffer = std::unique_ptr<Buffer>(new HeapBuffer(size));

        if (data) {
            buffer->setData(data);
        }

        return buffer;
    }

	inline ModernModule* GraphicsDriverBase::getModernModule() {
		return nullptr;
	}

	inline LegacyModule* GraphicsDriverBase::getLegacyModule() {
		return nullptr;
	}
}}

#endif  // __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
