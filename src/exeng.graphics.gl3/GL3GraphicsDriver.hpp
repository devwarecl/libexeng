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

#include <GLFW/glfw3.h>
#include <exeng/graphics/GraphicsDriverBase.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics { namespace gl3 {

    class GL3VertexBuffer;
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
        
        virtual void setVertexBuffer(const VertexBuffer* vertexBuffer) override;
        
        virtual void setIndexBuffer(const IndexBuffer* indexBuffer) override;
        
        virtual void setMaterial(const Material* material) override;
        
        virtual VertexBuffer* createVertexBuffer(const VertexFormat &vertexFormat, int vertexCount, const void* data) override;
        
        virtual IndexBuffer* createIndexBuffer(IndexFormat::Enum indexFormat, int indexCount, const void* data) override;
        
        virtual Texture* createTexture(TextureType::Enum TextureType, const exeng::Vector3f& TextureSize, const ColorFormat &format) override;
        
        virtual void setTransform(Transform::Enum transform, const exeng::Matrix4f& matrix) override;
        
        virtual void setViewport(const exeng::Rectf& viewport) override;
        
        virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount) override;
        
        virtual void pollEvents() override;
        
        virtual void addEventHandler(exeng::input::IEventHandler *handler) override;
        
        virtual void removeEventHandler(exeng::input::IEventHandler *handler) override;
        
        virtual void setDisplayMode(const DisplayMode &displayMode) override;
        
        virtual DisplayMode getDisplayMode() const override;
        
        virtual void restoreDisplayMode() override;
        
        virtual const VertexBuffer* getVertexBuffer() const override;
        
        virtual const IndexBuffer* getIndexBuffer() const override;
        
        virtual Shader* createShader( ShaderType::Enum type ) override;
        
        virtual ShaderProgram* createShaderProgram( ) override;
        
        virtual void raiseEvent(exeng::input::EventData &data) override;
        
    public:
        inline const GLFWwindow* getGLFWwindow() const {
            return this->window;
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
        GLFWwindow *window;
        
        Material *defaultMaterial;
        const ShaderProgram *defaultProgram;
        const Shader *defaultVertexShader;
        const Shader *defaultFragmentShader;
        
        std::list<exeng::input::IEventHandler*> eventHandlers;
        
        const GL3VertexBuffer *vertexBuffer;
        const GL3ShaderProgram *shaderProgram;
        
        bool initialized;
        bool renderingFrame;
        
        DisplayMode displayMode;
        
    private:
        static int initializedCount;
    };
}}}

#endif  // __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
