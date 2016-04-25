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

#ifndef __xe_gfx_graphicsdevice__
#define __xe_gfx_graphicsdevice__

#include <string>
#include <vector>
#include <memory>
#include <xe/Enum.hpp>
#include <xe/TFlags.hpp>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/Buffer.hpp>
#include <xe/input/InputManager.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/PixelFormat.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Shader.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/ModernModule.hpp>
#include <xe/gfx/LegacyModule.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Framebuffer clearing flags
     */
    struct ClearFlags : public Enum {
        enum Enum {
            Color = 1,
            Depth = 2,
            Stencil = 4,
			ColorDepth = Color | Depth
        };
        
        typedef TFlags<Enum> Flags;
    };
    
    struct DisplayStatus : public Enum {
        enum Enum { Window, Fullscreen };
    };

    /**
     * @brief The used graphics API backend.
     */
    struct GraphicsBackend : public Enum {
        enum Enum {
            Unknown,
            OpenGL_Legacy,
            OpenGL_Core,
            OpenGL_ES_1,
            OpenGL_ES_2,
            OpenGL_ES_3,
            Direct3D_9,
            Direct3D_10,
            Software
        };
    };
    
    /**
     * @brief Encapsulate a display mode.
     */
    struct GraphicsDeviceMode {
		int screenWidth = 800;
		int screenHeight = 600;

		int redBits = 8;
		int greenBits = 8;
		int blueBits = 8;
		int alphaBits = 8;

		int depthBits = 16;
		int stencilBits = 8;

        DisplayStatus::Enum status = DisplayStatus::Window;        
    };
    
	class EXENGAPI OpenGLGraphicsBackend {
	public:
		virtual ~OpenGLGraphicsBackend() {}

		virtual intptr_t getGLContext() const = 0;
		virtual intptr_t getOSContext() const = 0;
	};

    /**
     * @brief Software interface to graphics hardware
     */
	class EXENGAPI GraphicsDevice {
	public:
		typedef std::unique_ptr<GraphicsDevice> Ptr;

    public:
		virtual ~GraphicsDevice() {}
        
		virtual GraphicsDeviceMode getMode() const = 0;

        /**
         * @brief Initializes the graphics driver, with the settings included. 
         * Throws exception if the graphics drives can't be initialized with the
         * supplied settings.
         * @param displayMode The settings requested.
         */
        virtual void initialize(const GraphicsDeviceMode &mode = GraphicsDeviceMode()) = 0;
        
        /**
         * @brief Terminate the use of the graphics drivers, killing all resources 
         * created.
         */
        virtual void terminate() = 0;
        
        /**
         * @brief Checks if the GraphicsDevice instance has been initialized.
         * @return true if the graphics drivers has been correctly initialized, 
         * and false in other case.
         */
        virtual bool isInitialized() const = 0;
		
        /**
         * @brief Start the rendering of a new frame, clearing the previous one
         */
		virtual void beginFrame(const Vector4f &color={0.0f, 0.0f, 0.0f, 1.0f}, ClearFlags::Flags flags=ClearFlags::ColorDepth) = 0;
        
        /**
         * @brief Flip the backbuffer and the front buffer, showing the results on the screen.
         */
        virtual void endFrame() = 0;
        
        /**
         * @brief Set the currently used material
         */
        virtual void setMaterial(const Material* material) = 0;
        
        /**
         * @brief Get the currently used material
         */
        virtual const Material* getMaterial() const = 0;
        
        /**
         * @brief Create a new hardware-based vertex buffer. 
         */
        virtual Buffer::Ptr createVertexBuffer(const std::int32_t size, const void* data = nullptr) = 0;
        
		template<typename Type>
		Buffer::Ptr createVertexBuffer(const std::vector<Type> &vertices) {
			const int bufferSize = sizeof(Type) * vertices.size();
			const void *bufferData = vertices.data();

			return this->createVertexBuffer(bufferSize, bufferData);
		}

        /**
         * @brief Like CreateVertexBuffer, create a new hardware based index buffer.
         */
        virtual Buffer::Ptr createIndexBuffer(const std::int32_t size, const void* data = nullptr) = 0;

		template<typename Type>
		Buffer::Ptr createIndexBuffer(const std::vector<Type> &indices) {
			const int bufferSize = sizeof(Type) * indices.size();
			const void *bufferData = indices.data();

			return this->createIndexBuffer(bufferSize, bufferData);
		}

        MeshSubsetPtr createMeshSubset(Buffer::Ptr vertexBuffer, const VertexFormat *format);

		MeshSubsetPtr createMeshSubset(Buffer::Ptr vertexBuffer, const VertexFormat *format, Buffer::Ptr ibuffer, IndexFormat::Enum iformat);

		MeshSubsetPtr createMeshSubset(std::vector<Buffer::Ptr> vbuffers, const VertexFormat *vformat);

        /**
         * @brief Create a new mesh subset object.
         */
        virtual MeshSubsetPtr createMeshSubset(std::vector<Buffer::Ptr> vbuffers, const VertexFormat *vformat, Buffer::Ptr ibuffer, IndexFormat::Enum iformat) = 0;

        /**
         * @brief Bound the specified MeshSubset object.
         */
        virtual void setMeshSubset(const MeshSubset *meshSubset) = 0;
        
        /**
         * @brief Gets the currently bound MeshSubset.
         */
        virtual const MeshSubset* getMeshSubset() const = 0;

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

		virtual xe::input::InputManager* getInputManager() = 0;
        
        /** 
         * @brief Get the underlying graphics backend identification
         */
        virtual GraphicsBackend::Enum getBackend() const = 0;

        /**
         * @brief Get the graphics backend dependent,
         * @return 
         */        
        virtual const OpenGLGraphicsBackend* getOpenGLBackend() const = 0;

		/**
		 * @brief Render a mesh using the primitive rendering methods. Implementations can override this to offer improved performance.
		 */
		virtual void render(const xe::gfx::Mesh *mesh);
    };
}}

#endif
