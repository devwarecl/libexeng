/**
 * @file GraphicsDriver.hpp
 * @brief GraphicsDriver class API and support structures and enumerations.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#pragma once

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__

#include <string>
#include <vector>
#include <memory>
#include <xe/Enum.hpp>
#include <xe/TFlags.hpp>
#include <xe/Boundary.hpp>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/Buffer.hpp>
#include <xe/input/IInputManager.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/PixelFormat.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Shader.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/ModernModule.hpp>
#include <xe/gfx/LegacyModule.hpp>
#include <xe/gfx/BufferType.hpp>

namespace xe { namespace gfx {

    struct FramebufferFormat {
        int red=8, green=8, blue=8, alpha=8;
        int depth=8, stencil=8;
    };
    
    struct DisplayStatus : public Enum {
        enum Enum { Windowed, Fullscreen };
    };

    struct DisplayMode {
        int width=1200, height=768;
        FramebufferFormat framebuffer;
        DisplayStatus::Enum displayStatus = DisplayStatus::Windowed;
    };

    struct ClearFlags : public Enum {
        enum Enum {
            Color = 0x00000001,
            Depth = 0x00000002,
            Stencil = 0x00000004,
			ColorDepth = Color | Depth,
            All = Color | Depth | Stencil
        };
        
        typedef TFlags<Enum> Flags;
    };

    struct ClearData {
        Vector4f color = {0.2f, 0.2f, 0.8f, 1.0f};
        float depth = 0.0f;
        float stencil = 0.0f;
    };

    /**
     * @brief Software interface to graphics hardware
     */
	class EXENGAPI Device {
    public:
        typedef std::unique_ptr<Device> Ptr;

    public:
        virtual ~Device() {
            this->terminate();
        }
        
		virtual DisplayMode getDisplayMode() const = 0;

        /**
         * @brief Initializes the graphics driver, with the settings included. 
         * Throws exception if the graphics drives can't be initialized with the
         * supplied settings.
         * @param displayMode The settings requested.
         */
        virtual void initialize(const DisplayMode &displayMode=DisplayMode()) = 0;
        
        /**
         * @brief Terminate the use of the graphics drivers, killing all resources 
         * created.
         */
        virtual void terminate() = 0;
        
        /**
         * @brief Checks if the GraphicsDriver has been initialized.
         * @return true if the graphics drivers has been correctly initialized, 
         * and false in other case.
         */
        virtual bool isInitialized() const = 0;
		
        /**
         * @brief Start the rendering of a new frame, clearing the previous one
         */
        virtual void beginFrame(ClearFlags::Flags flags=ClearFlags::All, const ClearData& data=ClearData()) = 0;
        
        /**
         * @brief Flip the backbuffer and the front buffer
         */
        virtual void endFrame() = 0;
        
        /**
         * @brief Create a new hardware-based buffer. 
         */
        virtual Buffer::Ptr createBuffer(BufferType::Enum type, const std::int32_t size, const void* data = nullptr) = 0;
        
        /**
         * @brief Creates a new empty subset of geometric data.
         */
        virtual Subset::Ptr createSubset(const BufferPtrArray<Subset::BufferCount> &buffers, const BufferDescriptorArray<Subset::BufferCount> &descriptors) = 0;
    
        /**
         * @brief Bound the specified MeshSubset object.
         */
        virtual void setSubset(const Subset *meshSubset) = 0;
        
        /**
         * @brief Gets the currently bound MeshSubset.
         */
        virtual const Subset* getSubset() const = 0;

        /**
         * @brief Create a new texture object.
         */
		virtual TexturePtr createTexture(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
		virtual TexturePtr createTexture(const Vector3i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
		virtual TexturePtr createTextureCube(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
        
		virtual TexturePtr createTexture(const Image *image);

        /**
         * @brief Set the area of the screen that can be rendered
         */
        virtual void setViewport(const Rectf& viewport) = 0;
        
        /**
         * @brief Return the currently setted viewport.
         */
        virtual Rectf getViewport() const = 0;
        
        /**
         * @brief Render a primitive using the supplied parameter values and the current state of the graphics driver
		 * (current material and meshsubset).
         * @param primitive The primitive type.
         * @param count The vertex count to utilize from the currently setted meshsubset.
         */
        virtual void render(Primitive::Enum primitive, int count) = 0;
		
		/**
		 * @brief Get an interface to a fixed-function pipeline functionality.
		 */
		virtual LegacyModule* getLegacyModule() = 0;

		/**
		 * @brief Get an interface to a fully-programmable pipeline functionality.
		 */
		virtual ModernModule* getModernModule() = 0;

		virtual xe::input2::IInputManager* getInputManager() = 0;
    };

	typedef std::unique_ptr<GraphicsDriver> GraphicsDriverPtr;
}}

#endif
