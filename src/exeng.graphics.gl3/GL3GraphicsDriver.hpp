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
#include <exeng/graphics/GraphicsDriverBase.hpp>
#include <exeng/graphics/VertexFormat.hpp>

#include "GL3Buffer.hpp"
#include "GL3MeshSubset.hpp"

namespace exeng { namespace graphics { namespace gl3 {

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
    class GL3GraphicsDriver : public GraphicsDriverBase {    
    public:
        GL3GraphicsDriver();
        
        virtual ~GL3GraphicsDriver();
        
        virtual void initialize() override;
        
        virtual void initialize(const DisplayMode &displayMode) override;
        
        virtual void terminate() override;
        
        virtual bool isInitialized() const override;
        
        virtual void beginFrame(const Color &color, ClearFlags::Flags flags)  override;
        
        virtual void endFrame() override;
        
        virtual void setMaterial(const Material* material) override;
        
        virtual std::unique_ptr<Buffer> createVertexBuffer(const std::int32_t size, const void* data) override;
        
        virtual std::unique_ptr<Buffer> createIndexBuffer(const std::int32_t size, const void* data) override;
        
        virtual std::unique_ptr<Texture> createTexture(TextureType::Enum TextureType, const exeng::Vector3f& TextureSize, const ColorFormat &format) override;
        
        virtual void setTransform(Transform::Enum transform, const exeng::Matrix4f& matrix) override;
        
        virtual void setViewport(const exeng::Rectf& viewport) override;
        
        virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount) override;
        
        virtual void pollEvents() override;
        
        virtual void addEventHandler(exeng::input::IEventHandler *handler) override;
        
        virtual void removeEventHandler(exeng::input::IEventHandler *handler) override;
        
        virtual void setDisplayMode(const DisplayMode &displayMode) override;
        
        virtual DisplayMode getDisplayMode() const override;
        
        virtual void restoreDisplayMode() override;
        
        virtual std::unique_ptr<Shader> createShader( ShaderType::Enum type ) override;
        
        virtual std::unique_ptr<ShaderProgram> createShaderProgram( ) override;
        
        virtual void raiseEvent(exeng::input::EventData &data) override;
        
        virtual std::unique_ptr<MeshSubset> createMeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers, std::unique_ptr<Buffer> indexBuffer, const VertexFormat &format) override;

        virtual void setMeshSubset(MeshSubset *meshSubset) override;

        virtual MeshSubset* getMeshSubset() override;

        virtual const MeshSubset* getMeshSubset() const override;

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
        
        /**
        * @brief Update the matrix uniforms corresponding to the transformations.
        */
        void updateTransforms();
        
    private:
        std::unique_ptr<GL3Context> context;
        std::unique_ptr<Material> defaultMaterial;
        std::unique_ptr<const ShaderProgram> defaultProgram;
        std::list<exeng::input::IEventHandler*> eventHandlers;
        
        const GL3ShaderProgram *shaderProgram = nullptr;
        
        GL3Buffer *vertexBuffer = nullptr;
        GL3Buffer *indexBuffer = nullptr;
        GL3MeshSubset *meshSubset = nullptr;

        bool initialized = false;
        bool renderingFrame = false;
        
        DisplayMode displayMode;
        
    private:
        static int initializedCount;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
