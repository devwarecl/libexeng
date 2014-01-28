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
    
    virtual void initialize();
    
    virtual void initialize(const DisplayMode &displayMode);
    
    virtual void terminate();
    
    virtual bool isInitialized() const;
    
    virtual void beginFrame(const Color &color, ClearFlags::Flags flags) ;
    
    virtual void endFrame();
    
    virtual void setVertexBuffer(const VertexBuffer* vertexBuffer);
    
    virtual void setIndexBuffer(const IndexBuffer* indexBuffer);
    
    virtual void setMaterial(const Material* material);
    
    virtual VertexBuffer* createVertexBuffer(const VertexFormat &vertexFormat, 
                                             int vertexCount);
    
    virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, 
                                            int IndexCount  );
    
    virtual Texture* createTexture(TextureType TextureType, 
                                   const exeng::math::Vector3f& TextureSize, 
                                   const ColorFormat &format);
    
    virtual void setTransform(Transform transform, 
                              const exeng::math::Matrix4f& matrix);
    
    virtual void setViewport(const exeng::math::Rectf& viewport);
    
    virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount);
    
    virtual void pollEvents();
    
    virtual void addEventHandler(exeng::input::IEventHandler *handler);
    
    virtual void removeEventHandler(exeng::input::IEventHandler *handler);
    
    virtual void setDisplayMode(const DisplayMode &displayMode);
    
    virtual DisplayMode getDisplayMode() const;
    
    virtual void restoreDisplayMode();
    
    virtual const VertexBuffer* getVertexBuffer() const;
    
    virtual const IndexBuffer* getIndexBuffer() const;
    
    virtual Shader* createShader( ShaderType type );
    
    virtual ShaderProgram* createShaderProgram( );
    
    virtual void raiseEvent(exeng::input::EventData &data);
    
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
