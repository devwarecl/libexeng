/**
 * @file GL3GraphicsDriver.cpp
 * @brief Definition of the GL3 Graphics Driver class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "GL3Utils.hpp"
#include <GL/glfw.h>

#include "GL3GraphicsDriver.hpp"
#include "GL3Debug.hpp"
#include "GL3Shader.hpp"

#include <exeng/DataType.hpp>
#include <exeng/graphics/VertexFormat.hpp>

#include <map>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::input;

namespace exeng {
namespace graphics {
namespace gl3 {
    
    int GL3GraphicsDriver::initializedCount = 0;
    
    GL3GraphicsDriver::GL3GraphicsDriver() {
        this->vertexBuffer = nullptr;
        this->shaderProgram = nullptr;
        this->initialized = false;
    }
    
    
    GL3GraphicsDriver::~GL3GraphicsDriver() {
        this->terminate();
    }
    
    
    void 
    GL3GraphicsDriver::initialize(const DisplayMode &displayMode) {
        // NOTE: The use of the GLFW library to implement the initialization of the
        // OpenGL 3 Driver is only temporal.
        
        if (initializedCount > 0) {
            throw std::runtime_error("Only a single GL3 graphics driver can be"
                                     "initialized at time");
        }
        
        int mode = 0;
        int result = 0;
        
        if (!(result = ::glfwInit())) {
            throw std::runtime_error("GL3GraphicsDriver::initialize: "
                                     "GLFW initialization error.");
        }
        
        // Configure and create the context
        switch (displayMode.status) {
            case DisplayStatus::Window: mode |= GLFW_WINDOW; break;
            case DisplayStatus::Fullscreen: mode |= GLFW_FULLSCREEN; break;
        }
        
        ::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
        ::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
        ::glfwOpenWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
        result = ::glfwOpenWindow(displayMode.size.width, displayMode.size.height,
                                  displayMode.redBits, displayMode.greenBits, 
                                  displayMode.blueBits, displayMode.alphaBits,
                                  displayMode.depthBits, displayMode.stencilBits, 
                                  mode);
        
        if (!result) {
            throw std::runtime_error("GL3GraphicsDriver::initialize: "
                                     "GLFW open window error.");
        }
        
        ::glfwDisable(GLFW_AUTO_POLL_EVENTS);
        
        // Initialize the OpenGL 3 core functions
        ::ogl_LoadFunctions();
        
        this->initialized = true;
        ++GL3GraphicsDriver::initializedCount;
    }
    
    
    void 
    GL3GraphicsDriver::terminate() {
        if (this->initialized == true) {
            --GL3GraphicsDriver::initializedCount;
            
            //! TODO: Destroy all created objects
            ::glfwCloseWindow();
            ::glfwTerminate();
            
            this->initialized = false;
        }
    }
    
    
    bool 
    GL3GraphicsDriver::isInitialized() const {
        return this->initialized;
    }
    
    
    void 
    GL3GraphicsDriver::beginFrame(const Color &color, ClearFlags::Flags flags) {
        // Clears the OpenGL framebuffer
        GLenum clearFlags = 0L;
        
        clearFlags |= flags.getFlag(ClearFlags::Color) ? GL_COLOR_BUFFER_BIT : 0;
        clearFlags |= flags.getFlag(ClearFlags::Depth) ? GL_DEPTH_BUFFER_BIT : 0;
        clearFlags |= flags.getFlag(ClearFlags::Stencil) ? GL_STENCIL_BUFFER_BIT : 0;
        
        if (!clearFlags) {
            throw std::invalid_argument("GL3GraphicsDriver::beginScene: "
                                        "Flags must be non 0.");
        }
        
        ::glClearColor(color.red, color.green, color.blue, color.alpha);
        ::glClear(clearFlags);
        
        GL3_CHECK();
    }
    
    
    void 
    GL3GraphicsDriver::endFrame() {
        ::glFlush();
        ::glfwSwapBuffers();
        
        GL3_CHECK();
    }
    
    
    void 
    GL3GraphicsDriver::setVertexBuffer(const VertexBuffer* vertexBuffer) {
        
        if (this->vertexBuffer == vertexBuffer) {
            return;
        }
        
        if (vertexBuffer->getCreator() != this) {
            throw std::invalid_argument("GL3GraphicsDriver::setVertexBuffer: "
                                        "Invalid vertex buffer");
        }
        
        if (vertexBuffer->isEmpty() == true) {
            throw std::invalid_argument("GL3GraphicsDriver::setVertexBuffer: "
                                        "Vertex buffer can't be empty");
        }
        
        /*
        // Remove render state from previous vertex buffer
        if (this->vertexBuffer != nullptr) {
            ::glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer->getName());
            int fieldCount = this->vertexBuffer->getFormat().fields.size();
            for (int i=0; i<fieldCount; ++i) {
                ::glDisableVertexAttribArray(i);
            }
            
            GL3_CHECK();
        }
        */
        
        // Apply new render state
        if (vertexBuffer == nullptr) {
            this->vertexBuffer = nullptr;
            return;
        }
        
        this->vertexBuffer = static_cast<const GL3VertexBuffer*>(vertexBuffer);
        
        const VertexFormat &format = this->vertexBuffer->getFormat();
        int baseAttrib = 0;
        int offset = 0;
        DataType::Enum dataTypeKey;
        
        ::glBindVertexArray( this->vertexBuffer->getVertexArrayId() );
        ::glBindBuffer( GL_ARRAY_BUFFER, this->vertexBuffer->getName() );
        
        for (const VertexField& field : format.fields) {
            dataTypeKey = static_cast<DataType::Enum>(field.dataType.getValue());
            GLenum dataType = convDataType(dataTypeKey);
            
            ::glEnableVertexAttribArray(baseAttrib);
            ::glVertexAttribPointer(baseAttrib, field.count, 
                                    dataType, GL_FALSE, format.getSize(), 
                                    reinterpret_cast<const void*>(offset));
            
            offset += field.count * field.dataType.getSize();
            ++baseAttrib;
        }
        
        GL3_CHECK();
        
    }
    
    
    void 
    GL3GraphicsDriver::setIndexBuffer(const IndexBuffer* indexBuffer) {
    }
    
    
    void 
    GL3GraphicsDriver::setMaterial(const Material* material) {
        this->material = material;
    }
    
    
    VertexBuffer* 
    GL3GraphicsDriver::createVertexBuffer(const VertexFormat &format, 
                                          int count) {
        auto* vbuffer = new GL3VertexBuffer(this, format, count);
        
        this->objects.push_back(vbuffer);
        
        return vbuffer;
    }
    
    
    IndexBuffer* 
    GL3GraphicsDriver::createIndexBuffer( IndexFormat format, 
                                          int count ) {
        return nullptr;
    }
    
    
    Texture* 
    GL3GraphicsDriver::createTexture(TextureType type,
                                     const Vector3f& size) {
        return nullptr;
    }
    
    
    void 
    GL3GraphicsDriver::setTransform(Transform transform, 
                                    const Matrix4f& transformMatrix) {
		
		throw std::runtime_error("GL3GraphicsDriver::setTransform is not implemented");

        bool updateModelView = false;
        
        // 
        switch (transform) {
            case Transform::View: {
            this->view = transformMatrix; 
            updateModelView = true; 
            break;
            }
            
            case Transform::World: {
            this->model = transformMatrix;
            updateModelView = true; 
            break;
            }
            
        case Transform::Projection: {
            this->projection = transformMatrix; 
            break;
            }
        }
        
        /*
        // Update the current OpenGL transformation matrix
        if (updateModelView == true) {
            this->modelView = this->model * this->view;
            
            ::glMatrixMode(GL_MODELVIEW);
            GL3_CHECK();
            
            ::glLoadMatrixf(this->modelView.getPtr());
            GL3_CHECK();
        } else {
            ::glMatrixMode(GL_PROJECTION);
            GL3_CHECK();
            ::glLoadMatrixf(this->projection.getPtr());
            GL3_CHECK();
        }
        
        GL3_CHECK();
        */
    }
    
    
    void GL3GraphicsDriver::setViewport(const Rectf& viewport) {
        auto minEdge = viewport.getMin();
        auto size = viewport.getSize();
        
        int x = static_cast<int>(minEdge.x);
        int y = static_cast<int>(minEdge.y);
        int w = static_cast<int>(size.width);
        int h = static_cast<int>(size.height);
        
        if (h == 0) {
            h = 1;
        }
        
        this->viewport = viewport;
        
        ::glViewport(x, y, w, h);
        GL3_CHECK();
    }
    
    
    void 
    GL3GraphicsDriver::render(Primitive::Enum ptype, int count) {
        if (this->vertexBuffer == nullptr) {
            throw std::runtime_error("GL3GraphicsDriver::render: "
                                     "A current binded vertex buffer must be setted.");
        }
        
        // Check if the current setted buffer is the same
        GLint name;
        ::glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &name);
        assert( name != 0 );
        assert( name == this->vertexBuffer->getName() );
        
        //! TODO: Implement rendering path with the index buffer in the future.
        GLenum primitive = convPrimitive(ptype);
        ::glDrawArrays(primitive, 0, count);
        
        GL3_CHECK();
    }
    
    
    void GL3GraphicsDriver::pollEvents() {
        ::glfwPollEvents();
        
        //! TODO: notify the event handlers for events
    }
    
    
    void GL3GraphicsDriver::addEventHandler(IEventHandler *handler) {
        this->eventHandlers.push_back(handler);
    }
    
    
    void GL3GraphicsDriver::removeEventHandler(IEventHandler *handler) {
        this->eventHandlers.remove(handler);
    }
    
    
    void GL3GraphicsDriver::setDisplayMode(const DisplayMode &displayMode) {
        throw std::runtime_error("GL3GraphicsDriver::setDisplayMode: Not implemented.");
    }
    
    DisplayMode GL3GraphicsDriver::getDisplayMode() const {
        throw std::runtime_error("GL3GraphicsDriver::getDisplayMode: Not implemented.");
    }
    
    void GL3GraphicsDriver::restoreDisplayMode() {
        throw std::runtime_error("GL3GraphicsDriver::restoreDisplayMode: Not implemented.");
    }
    
    const VertexBuffer* GL3GraphicsDriver::getVertexBuffer() const {
        return this->vertexBuffer;
    }
    
    const IndexBuffer* GL3GraphicsDriver::getIndexBuffer() const {
        throw std::runtime_error("GL3GraphicsDriver::getIndexBuffer: Not implemented.");
    }
    
    
    Shader* GL3GraphicsDriver::createShader( ShaderType type ) {
        //! TODO: Append the shader object to the pool
        return new GL3Shader(type);
    }
    
    
    ShaderProgram* GL3GraphicsDriver::createShaderProgram( ) {
        //! TODO: Append the shader program to the pool
        return new GL3ShaderProgram();
    }
    
    
    void GL3GraphicsDriver::setShaderProgram(const ShaderProgram *program) {
        if (program == nullptr) {
            throw std::invalid_argument("GL3GraphicsDriver::setShaderProgram: "
                                        "Expected a non-null shader program");
        }
        
        if ( program->getTypeInfo() != TypeInfo::get<GL3ShaderProgram>() ) {
            throw std::invalid_argument("GL3GraphicsDriver::setShaderProgram: "
                                        "Expected a shader program of type GL3ShaderProgram");
        }
        
        if ( program->isLinked() == false ) {
            throw std::runtime_error("GL3GraphicsDriver::setShaderProgram: "
                                     "The shader program must be linked by client code.");
        }
        
        //! TODO: Check for an empty shader program
        auto *shaderProgram = static_cast<const GL3ShaderProgram *>(program);
		assert( shaderProgram->getProgramId() != 0 );
        ::glUseProgram(shaderProgram->getProgramId());
        
        this->shaderProgram = shaderProgram;
        
        GL3_CHECK();
    }
}
}
}
