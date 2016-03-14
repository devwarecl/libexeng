/**
 * @file GraphicsDriverGL3.hpp
 * @brief Definition of the GL3 Graphics Driver class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
#define __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__

#include <list>
#include <memory>
#include <exception>

#include <GLFW/glfw3.h>
#include <xe/input/Event.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/GraphicsDriverBase.hpp>
#include <xe/gfx/VertexFormat.hpp>

#include "Context.hpp"
#include "InputManagerGLFW.hpp"
#include "BufferGL3.hpp"
#include "MeshSubsetGL3.hpp"
#include "ShaderProgramGL3.hpp"

namespace xe { namespace gfx { namespace gl3 {
    
    class ShaderProgramGL3;

    /**
     * @brief GraphicsDriver implemented using OpenGL 3.x
     */
    class GraphicsDriverGL3 : public GraphicsDriverBase, public ModernModule, public OpenGLGraphicsBackend { 
    public:
        GraphicsDriverGL3();
        
        virtual ~GraphicsDriverGL3();
        
        virtual void initialize() override;
        
        virtual void initialize(const DisplayMode &displayMode) override;
        
        virtual void terminate() override;
        
        virtual bool isInitialized() const override;
        
        virtual void beginFrame(const Vector4f &color, ClearFlags::Flags flags)  override;
        
        virtual void endFrame() override;
        
        virtual void setMaterial(const Material* material) override;
        
        virtual std::unique_ptr<Buffer> createVertexBuffer(const std::int32_t size, const void* data) override;
        
        virtual std::unique_ptr<Buffer> createIndexBuffer(const std::int32_t size, const void* data) override;
        
        virtual TexturePtr createTexture(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) override;	
		virtual TexturePtr createTexture(const Vector3i& size, PixelFormat::Enum format, const void *data = nullptr) override;
		virtual TexturePtr createTextureCube(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) override;
        
        virtual void setViewport(const xe::Rectf& viewport) override;
        
        virtual void render(xe::gfx::Primitive::Enum primitiveType, int vertexCount) override;
        
        virtual DisplayMode getDisplayMode() const override;
        
        virtual ShaderPtr createShader( ShaderType::Enum type ) override;
        
        virtual ShaderProgramPtr createShaderProgram( ) override;
        
        virtual MeshSubsetPtr createMeshSubset(std::vector<BufferPtr> vertexBuffers, const VertexFormat *format, BufferPtr indexBuffer, IndexFormat::Enum iformat) override;

        virtual void setMeshSubset(const MeshSubset *meshSubset) override;
        
        virtual const MeshSubset* getMeshSubset() const override;

		virtual ModernModule* getModernModule() override;

		inline const ShaderProgram* getShaderProgram() const override {
			return this->shaderProgram;
		}

		virtual void setProgramMatrix(const std::string &name, const int count, const xe::Matrix4f *matrices) override;

		virtual void setProgramParam(const std::string &name, const int count, const int dim, DataType::Enum dataType, const void *value) override;

		virtual InputManagerGLFW* getInputManager() override {
			return &this->inputManager;
		}

        virtual GraphicsBackend::Enum getBackend() const override {
            return GraphicsBackend::OpenGL_Core;
        }

        virtual const OpenGLGraphicsBackend* getOpenGLBackend() const override {
			return this;
		}
        
		virtual intptr_t getGLContext() const override;

		virtual intptr_t getOSContext() const override;

		virtual void setShaderProgram(const ShaderProgram *program) override;

		// virtual const ShaderProgram* getShaderProgram() const override;

    public:
        inline const GLFWwindow* getGLFWwindow() const {
            return context.window;
        }
        
    private:
        /**
        * @brief Apply the render states of the material
        */
        void preRenderMaterial(const Material *material);
        
        /**
        * @brief Restore render state to originals
        */
        void postRenderMaterial(const Material *material);

    private:
        Context context;
        
        const ShaderProgramGL3 *shaderProgram = nullptr;
        const BufferGL3 *vertexBuffer = nullptr;
        const BufferGL3 *indexBuffer = nullptr;
        const MeshSubsetGL3 *meshSubset = nullptr;

        bool initialized = false;
        bool renderingFrame = false;
        
        DisplayMode displayMode;
        InputManagerGLFW inputManager;

    private:
        static int initializedCount;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
