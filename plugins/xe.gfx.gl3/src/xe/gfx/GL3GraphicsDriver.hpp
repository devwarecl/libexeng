/**
 * @file GL3GraphicsDriver.hpp
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
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/GraphicsDriverBase.hpp>
#include <xe/gfx/VertexFormat.hpp>

#include "GL3Buffer.hpp"
#include "GL3MeshSubset.hpp"
#include "GL3ShaderProgram.hpp"

namespace xe { namespace gfx { namespace gl3 {

    struct GL3Context {
        GLFWwindow *window = nullptr;

        inline GL3Context()  {
            if (!::glfwInit()) {
                throw std::runtime_error("GL3Context::GL3Context -> GLFW initialization error.");
            }
        }

        inline ~GL3Context() {
            ::glfwDestroyWindow(window);
            ::glfwTerminate();
        }
    };
    
    class GL3ShaderProgram;

    /**
     * @brief GraphicsDriver implemented using OpenGL 3.x
     */
    class GL3GraphicsDriver : public GraphicsDriverBase, public ModernModule {    
    public:
        GL3GraphicsDriver();
        
        virtual ~GL3GraphicsDriver();
        
        virtual void initialize() override;
        
        virtual void initialize(const DisplayMode &displayMode) override;
        
        virtual void terminate() override;
        
        virtual bool isInitialized() const override;
        
        virtual void beginFrame(const Vector4f &color, ClearFlags::Flags flags)  override;
        
        virtual void endFrame() override;
        
        virtual void setMaterial(const Material* material) override;
        
        virtual std::unique_ptr<Buffer> createVertexBuffer(const std::int32_t size, const void* data) override;
        
        virtual std::unique_ptr<Buffer> createIndexBuffer(const std::int32_t size, const void* data) override;
        
        virtual TexturePtr createTexture(const Vector2i& size, const ColorFormat &format, const void *data = nullptr) override;	
		virtual TexturePtr createTexture(const Vector3i& size, const ColorFormat &format, const void *data = nullptr) override;
		virtual TexturePtr createTextureCube(const Vector2i& size, const ColorFormat &format, const void *data = nullptr) override;
        
        virtual void setViewport(const xe::Rectf& viewport) override;
        
        virtual void render(xe::gfx::Primitive::Enum primitiveType, int vertexCount) override;
        
        virtual void pollEvents() override;
        
        virtual void addEventHandler(xe::input::IEventHandler *handler) override;
        
        virtual void removeEventHandler(xe::input::IEventHandler *handler) override;
        
        virtual DisplayMode getDisplayMode() const override;
        
        virtual std::unique_ptr<Shader> createShader( ShaderType::Enum type ) override;
        
        virtual std::unique_ptr<ShaderProgram> createShaderProgram( ) override;
        
        virtual void raiseEvent(xe::input::EventData &data) override;
        
        virtual std::unique_ptr<MeshSubset> createMeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers, std::unique_ptr<Buffer> indexBuffer, const VertexFormat &format) override;

        virtual void setMeshSubset(const MeshSubset *meshSubset) override;
        
        virtual const MeshSubset* getMeshSubset() const override;

		virtual ModernModule* getModernModule() override;

		inline const GL3ShaderProgram* getShaderProgram() const {
			return static_cast<const GL3ShaderProgram*>(this->getMaterial()->getShaderProgram());
		}

    public:
        inline const GLFWwindow* getGLFWwindow() const {
            return this->context->window;
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

		virtual void setProgramGlobal(const std::string &globalName, const Vector4f &value) override;

		virtual void setProgramGlobal(const std::string &globalName, const Matrix4f &value) override;

		virtual void setProgramGlobal(const int index, const Vector4f &value) override;

		virtual void setProgramGlobal(const int index, const Matrix4f &value) override;

    private:
        std::unique_ptr<GL3Context> context;
        std::list<xe::input::IEventHandler*> eventHandlers;
        
        const GL3ShaderProgram *shaderProgram = nullptr;
        const GL3Buffer *vertexBuffer = nullptr;
        const GL3Buffer *indexBuffer = nullptr;
        const GL3MeshSubset *meshSubset = nullptr;

        bool initialized = false;
        bool renderingFrame = false;
        
        DisplayMode displayMode;
        
    private:
        static int initializedCount;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
