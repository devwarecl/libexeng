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

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__

#include <string>
#include <vector>

#include <exeng/Object.hpp>
#include <exeng/TFlags.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/math/TMatrix.hpp>

#include <exeng/input/IEventRaiser.hpp>

#include <exeng/graphics/Color.hpp>
#include <exeng/graphics/PixelFormat.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/Screen.hpp>
#include <exeng/graphics/Primitive.hpp>
#include <exeng/graphics/Shader.hpp>
#include <exeng/graphics/ShaderProgram.hpp>

namespace exeng {
namespace graphics {

/**
 * @brief Transformation types
 */
enum class Transform {
    View,
    World,
    Projection
};

/**
 * @brief Framebuffer clearing flags
 */
namespace ClearFlags {
    enum Enum {
        Color = 0x00000001,
        Depth = 0x00000002,
        Stencil  = 0x00000004
    };
    
    typedef TFlags<Enum> Flags;
}

class EXENGAPI Texture;
class EXENGAPI VertexBuffer;
class EXENGAPI IndexBuffer;
class EXENGAPI Material;

enum class DisplayStatus {
    Window, Fullscreen
};

/**
 * @brief Encapsulate a display mode.
 */
struct DisplayMode {
    exeng::math::Size2i size;                       //! Width and height, in pixels.
    int redBits, greenBits, blueBits, alphaBits;    //! Frame buffer colors.
    int depthBits, stencilBits;                     //! Frame buffer support
    DisplayStatus status;                           //! Fullscreen or window?
    
    inline DisplayMode() : size(800, 600) {
        this->redBits = this->greenBits = this->blueBits = this->alphaBits = 0;
        this->depthBits = this->stencilBits = 0;
        this->status = DisplayStatus::Window;
    }
    
    
    inline DisplayMode(exeng::math::Size2i size, 
                       int redBits, int greenBits, int blueBits, int alphaBits) {
        
        this->size = size;
        this->redBits = redBits;
        this->greenBits = greenBits;
        this->blueBits = blueBits;
        this->alphaBits = alphaBits;
        this->depthBits = 0;
        this->stencilBits = 0;
        this->status = DisplayStatus::Window;
    }
    
    
    inline DisplayMode(exeng::math::Size2i size, 
                       int redBits, int greenBits, int blueBits, int alphaBits,
                       int depthBits, int stencilBits, DisplayStatus status) {
        
        this->size = size;
        this->redBits = redBits;
        this->greenBits = greenBits;
        this->blueBits = blueBits;
        this->alphaBits = alphaBits;
        this->depthBits = depthBits;
        this->stencilBits = stencilBits;
        this->status = status;
    }
};


/**
 * @brief Software interface to graphics hardware (Ha!)
 */
class EXENGAPI GraphicsDriver : public Object, public exeng::input::IEventRaiser {
public:
    virtual ~GraphicsDriver();
    
    /**
     * @brief Initializes the graphics driver, with the settings included. 
     * Throws exception if the graphics drives can't be initialized with the
     * supplied settings.
     * @param displayMode The settings requested.
     */
    virtual void initialize(const DisplayMode &displayMode) = 0;
    
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
     * @brief Set the current display mode
     */
    virtual void setDisplayMode(const DisplayMode &displayMode) = 0;
    
    /**
     * @brief Get the current display mode.
     */
    virtual DisplayMode getDisplayMode() const = 0;
    
    /**
     * @brief Restore the current display mode to the original one.
     */
    virtual void restoreDisplayMode() = 0;
    
    /**
     * @brief Start the rendering of a new frame, clearing the previous one
     */
    virtual void beginFrame(const Color &color, 
                            ClearFlags::Flags flags = ClearFlags::Color | ClearFlags::Depth) = 0;
    
    /**
     * @brief Flip the backbuffer and the front buffer
     */
    virtual void endFrame() = 0;
    
    /**
     * @brief Set the currently used vertex buffer
     */
    virtual void setVertexBuffer(const VertexBuffer* vertexBuffer) = 0;
    
    /**
     * @brief Set the current index buffer
     */
    virtual void setIndexBuffer(const IndexBuffer* indexBuffer) = 0;
    
    /**
     * @brief Get the vertex buffer currently used for rendering operations.
     */
    virtual const VertexBuffer* getVertexBuffer() const = 0;
    
    /**
     * @brief Get the currently used index buffer.
     */
    virtual const IndexBuffer* getIndexBuffer() const = 0;
    
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
    virtual VertexBuffer* createVertexBuffer(const VertexFormat &vertexFormat, int vertexCount) = 0;
    
    /**
     * @brief Like CreateVertexBuffer, create a new hardware based index buffer.
     */
    virtual IndexBuffer* createIndexBuffer( IndexFormat indexFormat, int indexCount) = 0;
    
    /**
     * @brief Create a new texture object.
     */
    virtual Texture* createTexture(TextureType textureType, const exeng::math::Vector3f& textureSize) = 0;
    
    /**
     * @brief Set the current transformation matrix
     */
    virtual void setTransform(Transform transform, const exeng::math::Matrix4f& matrix) = 0;
    
    /**
     * @brief Get the current transformation applied on the device.
     */
    virtual exeng::math::Matrix4f getTransform(Transform transform) = 0;
    
    /**
     * @brief Set the area of the screen that can be rendered
     */
    virtual void setViewport(const exeng::math::Rectf& viewport) = 0;
    
    /**
     * @brief Return the currently setted viewport.
     */
    virtual exeng::math::Rectf getViewport() const = 0;
    
    /**
     * @brief Render, using the specified primitive and the currently setted material, 
     * vertex and index buffers, if any. 
     * @param primitive The primitive type.
     * @param count The vertex count to utilize from the currently setted buffers.
     */
    virtual void render(exeng::graphics::Primitive::Enum primitive, int count) = 0;
    
    /**
     * @brief createShader
     * @param type
     * @return 
     */
    virtual Shader* createShader( ShaderType type ) = 0;
    
    /**
     * @brief Create a new shader program, specific to the current graphics driver.
     * @return A new shader program, instance of an derived implementation class of the 
     * ShaderProgram abstract class.
     */
    virtual ShaderProgram* createShaderProgram( ) = 0;
    
    /**
     * @brief Set the currently used shader program used in rendering calls.
     * @param program
     */
    virtual void setShaderProgram(const ShaderProgram *program) = 0;
};
}
}

#endif
