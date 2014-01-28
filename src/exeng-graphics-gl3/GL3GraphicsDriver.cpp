/**
 * @file GL3GraphicsDriver.cpp
 * @brief Implementation of the GL3 Graphics Driver class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "GL3Utils.hpp"
#include <GLFW/glfw3.h>

#include "GL3GraphicsDriver.hpp"
#include "GL3Plugin.hpp"
#include "GL3GraphicsDriverFactory.hpp"
#include "GL3Debug.hpp"
#include "GL3Shader.hpp"
#include "GL3Texture.hpp"
#include "GL3VertexBuffer.hpp"
#include "GL3Shader.hpp"
#include "GL3ShaderProgram.hpp"

#include <exeng/DataType.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/input/IEventHandler.hpp>

#include <map>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;
using namespace exeng::input;

namespace exeng { namespace graphics { namespace gl3 {

// TODO: Add the specific transformation variables
static const std::string defaultVSSource = std::string(
            "#version 330 \n"
            "layout(location=0) in vec4 position; \n"
            "layout(location=1) in vec2 texCoord; \n"
            "out vec2 uv; \n"
            "\n"
            "void main() { \n"
            "    gl_Position = position; \n"
            "    uv = texCoord; \n"
            "}\n"
);

static const std::string defaultFSSource = std::string(
            "#version 330 \n"
            "in vec2 uv; \n"
            "out vec4 outputColor; \n"
            "uniform sampler2D texSampler2D; \n"
            "void main() { \n"
            "outputColor = texture(texSampler2D, uv); \n"
            "}\n"
);

static void closeEvent(GLFWwindow *window) {
    auto *plugin = exeng::graphics::gl3::currentPlugin;
    
    CloseEventData closeEventData(CloseReason::Unknown);
    
    plugin->getFactory()->getGraphicsDriver(window)->raiseEvent(closeEventData);
}

// static InputEventData inputEventData;

static void keyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
	ButtonCode::Enum code;
	switch (key) {
		case GLFW_KEY_ESCAPE:	code = ButtonCode::KeyEsc;		break;
		case GLFW_KEY_LEFT:		code = ButtonCode::KeyLeft;		break;
		case GLFW_KEY_RIGHT:	code = ButtonCode::KeyRight;	break;
		case GLFW_KEY_UP:		code = ButtonCode::KeyUp;		break;
		case GLFW_KEY_DOWN:		code = ButtonCode::KeyDown;		break;
		case GLFW_KEY_SPACE:	code = ButtonCode::KeySpace;	break;
		case GLFW_KEY_ENTER:	code = ButtonCode::KeyEnter;	break;
		default: code = ButtonCode::None;
	}

	ButtonStatus::Enum status = ButtonStatus::Press;
	if (action == GLFW_RELEASE) {
		status = ButtonStatus::Release;
	} else if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		status = ButtonStatus::Press;
	}

	InputEventData inputEventData;
	inputEventData.buttonCode = code;
	inputEventData.buttonStatus = status;
	
	auto *plugin = exeng::graphics::gl3::currentPlugin;
    
    plugin->getFactory()->getGraphicsDriver(window)->raiseEvent(inputEventData);
}

int GL3GraphicsDriver::initializedCount = 0;

GL3GraphicsDriver::GL3GraphicsDriver() {
    this->vertexBuffer = nullptr;
    this->shaderProgram = nullptr;
    this->initialized = false;
    this->defaultVertexShader = nullptr;
    this->defaultFragmentShader = nullptr;
    this->defaultProgram = nullptr;
    this->defaultMaterial = new Material();
    this->renderingFrame = false;
    this->window = nullptr;
}

GL3GraphicsDriver::~GL3GraphicsDriver() {
    boost::checked_delete(this->defaultMaterial);
    
    boost::checked_delete(this->defaultProgram);
    boost::checked_delete(this->defaultVertexShader);
    boost::checked_delete(this->defaultFragmentShader);

	this->terminate();
}


void GL3GraphicsDriver::initialize() {
    this->initialize(DisplayMode());
}


void GL3GraphicsDriver::initialize(const DisplayMode &displayMode) {
    if (initializedCount > 0) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::initialize: ";
        msg += "Only a single GL3 graphics driver can be initialized at time";
        
        throw std::runtime_error(msg);
    }
    
    // initialize GLFW
    if (!::glfwInit()) {
        throw std::runtime_error("GL3GraphicsDriver::initialize: GLFW initialization error.");
    }
    
    // Configure and create the context
    GLFWmonitor *monitor = nullptr;
    
    switch (displayMode.status) {
        case DisplayStatus::Window: monitor = nullptr; break;
        case DisplayStatus::Fullscreen: monitor = ::glfwGetPrimaryMonitor() ; break;
    }
    
	::glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    ::glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    
    int width = displayMode.size.width;
    int height = displayMode.size.height;
    
    this->window = ::glfwCreateWindow(width, height, "exeng-graphics-gl3 Window", monitor, NULL);
    if (this->window == nullptr) {
        ::glfwTerminate();
        throw std::runtime_error("GL3GraphicsDriver::GL3GraphicsDriver: Cannot create a GLFW Window.");
    }
    
    ::glfwMakeContextCurrent(this->window);
    
    // Set the 
    ::glfwSetWindowCloseCallback(this->window, closeEvent);
	::glfwSetKeyCallback(this->window, keyEvent);

    this->setTransformName(Transform::World, "WorldTransform");
    this->setTransformName(Transform::View, "ViewTransform");
    this->setTransformName(Transform::Projection, "ProjectionTransform");
    
    // Initialize the OpenGL 3 core functions
    ::ogl_LoadFunctions();
    
    // Default vertex shader
    auto vertexShader = this->createShader(ShaderType::Vertex);
    
    vertexShader->setSourceCode(defaultVSSource);
    vertexShader->compile();
    
    // Default pixel shader
    auto fragmentShader = this->createShader(ShaderType::Fragment);
    
    fragmentShader->setSourceCode(defaultFSSource);
    fragmentShader->compile();
    
    // Default shader program
    auto shaderProgram = this->createShaderProgram();
    
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);
    shaderProgram->link();
    
    // Default material
    this->defaultMaterial->setShaderProgram(shaderProgram);
    
    // Hold all the default objects
    this->defaultVertexShader = vertexShader;
    this->defaultFragmentShader = fragmentShader;
    this->defaultProgram = shaderProgram;
    
    this->displayMode = displayMode;
    
    this->initialized = true;
    ++GL3GraphicsDriver::initializedCount;
}

void GL3GraphicsDriver::terminate() {
    if (this->initialized == true) {
        --GL3GraphicsDriver::initializedCount;
        
        //! TODO: Destroy all created objects
        ::glfwDestroyWindow(this->window);
        ::glfwTerminate();
        
        this->initialized = false;
    }
}

bool GL3GraphicsDriver::isInitialized() const {
    return this->initialized;
}

void GL3GraphicsDriver::beginFrame(const Color &color, ClearFlags::Flags flags) {
#if defined(EXENG_DEBUG)
    if (this->renderingFrame == true) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::beginFrame: ";
        msg += "Can't rendering a new frame if the current one hasn't been completed.";
        
        throw std::logic_error(msg);
    }       
#endif
    GLenum clearFlags = 0L;
    clearFlags |= flags.getFlag(ClearFlags::Color) ? GL_COLOR_BUFFER_BIT : 0;
    clearFlags |= flags.getFlag(ClearFlags::Depth) ? GL_DEPTH_BUFFER_BIT : 0;
    clearFlags |= flags.getFlag(ClearFlags::Stencil) ? GL_STENCIL_BUFFER_BIT : 0;
    
#if defined(EXENG_DEBUG)
    if (!clearFlags) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::beginScene: ";
        msg += "Flags must be non 0.";
        
        throw std::invalid_argument(msg);
    }
#endif
    
    ::glClearColor(color.red, color.green, color.blue, color.alpha);
    ::glClear(clearFlags);
    
    this->renderingFrame = true;
    
    GL3_CHECK();
}


void GL3GraphicsDriver::endFrame() {
#if defined(EXENG_DEBUG)
    if (this->renderingFrame == false) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::endFrame: ";
        msg += "Invalid call because must start a new frame first, via the beginFrame method.";
        
        throw std::logic_error(msg);
    }       
#endif
    ::glFlush();
    ::glfwSwapBuffers(this->window);
    
    this->renderingFrame = false;
    
    GL3_CHECK();
}


void GL3GraphicsDriver::setVertexBuffer(const VertexBuffer* vertexBuffer) {
#if defined(EXENG_DEBUG)
    if (vertexBuffer->getResourceFactory() != this) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::setVertexBuffer: ";
        msg += "The vertex buffer must have been created by the current graphics driver.";
        
        throw std::invalid_argument(msg);
    }
    
    if (vertexBuffer->isEmpty() == true) {
        std::string msg;
        
        msg += "GL3GraphicsDriver::setVertexBuffer: ";
        msg += "Vertex buffer can't be empty";
        
        throw std::invalid_argument(msg);
    }
#endif
    if (this->vertexBuffer == vertexBuffer) {
        return;
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


void GL3GraphicsDriver::setIndexBuffer(const IndexBuffer* indexBuffer) {
	// TODO: Implement
}


void  GL3GraphicsDriver::setMaterial(const Material* material) {
#if defined (EXENG_DEBUG)
    // Check texture type info
    
    if (material->checkTextureType(TypeInfo::get<GL3Texture>()) == false) {
        throw std::runtime_error("GL3GraphicsDriver::setMaterial: The supplied texture class implementation must be GL3Texture.");
    }
        
    // Check if the  textures were created by this GL3GraphicsDriver.
    const int layerCount = material->getLayerCount();
    const MaterialLayer *layer = nullptr;
    
    for (int i=0; i<layerCount; ++i) {
        layer = material->getLayer(i);
        
        if (layer->hasTexture() == true && layer->getTexture()->getResourceFactory() != this ) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::setMaterial: ";
            msg += "The textures used by this material are not valid.";
            
            throw std::logic_error(msg);
        }
    }
    
    // Check for shader program info and status
    if ( material->getShaderProgram() != nullptr ) {
        if ( material->getShaderProgram()->getTypeInfo() != TypeInfo::get<GL3ShaderProgram>() ) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::setMaterial: ";
            msg += "Expected a shader program of type GL3ShaderProgram";
            
            throw std::invalid_argument(msg);
        }
        
        if ( material->getShaderProgram()->isLinked() == false ) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::setMaterial: ";
            msg += "The shader program must be linked by client code.";
            
            throw std::logic_error(msg);
        }
    }
#endif
    if (this->material != nullptr && this->material != material) {
        this->postRenderMaterial(this->material);
    }
    
    if (material == nullptr) {
        material = this->defaultMaterial;
    }
    
    this->preRenderMaterial(material);
    this->material = material;
}


VertexBuffer* GL3GraphicsDriver::createVertexBuffer(const VertexFormat &format, int count) {
    auto* vbuffer = new GL3VertexBuffer(this, format, count);
    this->addResource(vbuffer);
    
    return vbuffer;
}


IndexBuffer* GL3GraphicsDriver::createIndexBuffer(IndexFormat format, int count) {
    throw std::runtime_error("GL3GraphicsDriver::createIndexBuffer: Not yet implemented");
}


Texture* GL3GraphicsDriver::createTexture(TextureType type, const Vector3f& size, const ColorFormat &format) {
    auto *texture = new GL3Texture(this, type, size, format);
    this->addResource(texture);
    
    return texture;
}


void GL3GraphicsDriver::setTransform(Transform transform, const Matrix4f& transformMatrix) {
    const int index = static_cast<const int>(transform);
    this->transforms[index] = transformMatrix;
    
    this->updateTransforms();
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


void GL3GraphicsDriver::render(Primitive::Enum ptype, int count) {
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
    throw std::runtime_error("GL3GraphicsDriver::setDisplayMode: Not implemented yet.");
}

DisplayMode GL3GraphicsDriver::getDisplayMode() const {
    return this->displayMode;
}

void GL3GraphicsDriver::restoreDisplayMode() {
    throw std::runtime_error("GL3GraphicsDriver::restoreDisplayMode: Not implemented yet.");
}

const VertexBuffer* GL3GraphicsDriver::getVertexBuffer() const {
    return this->vertexBuffer;
}

const IndexBuffer* GL3GraphicsDriver::getIndexBuffer() const {
    throw std::runtime_error("GL3GraphicsDriver::getIndexBuffer: Not implemented.");
}


Shader* GL3GraphicsDriver::createShader( ShaderType type ) {
    auto *resource = new GL3Shader(this, type);
    this->addResource(resource);
    
    return resource;
}


ShaderProgram* GL3GraphicsDriver::createShaderProgram( ) {
    auto *resource = new GL3ShaderProgram(this);
    this->addResource(resource);
    
    return resource;
}


void GL3GraphicsDriver::preRenderMaterial(const Material *material) {
    assert(material != nullptr);
    
    const GL3Texture *texture = nullptr;
    const MaterialLayer *layer;
    GLenum textureType;
    GLenum textureId;
    
    // Set the texture state
    for(int i=0; i<material->getLayerCount(); ++i) {
        layer = material->getLayer(i);
        
        if (layer->hasTexture() == true) {
            texture = static_cast<const GL3Texture*>(layer->getTexture());
            textureType = convTextureType(texture->getType());
            textureId = texture->getTextureId();
            
            ::glActiveTexture(GL_TEXTURE0 + i);
            ::glBindTexture(textureType, textureId);
        }
    }
    
    // set the shader program state
    const GL3ShaderProgram *shaderProgram = nullptr;
    
    if (material->getShaderProgram() != nullptr) {
        shaderProgram = static_cast<const GL3ShaderProgram*>(material->getShaderProgram());
    } else {
        shaderProgram = static_cast<const GL3ShaderProgram*>(this->defaultProgram);
    }
    
    GLint programId = shaderProgram->getProgramId();
    ::glUseProgram(programId);
    
    // Set material attributes
    TypeInfo info;
    std::string name;
    GLint uniformLocation = 0;
    
    for(int i=0; i<material->getPropertyNameCount(); ++i ) {
        info = material->getPropertyType(i);
        name = material->getPropertyName(i);
        
        uniformLocation = ::glGetUniformLocation(programId, name.c_str());
        
        if (uniformLocation > -1) {
            if (info == TypeInfo::get<float>()) {
                ::glUniform1f( uniformLocation, material->getPropertyf( name ) );
            } else if (info == TypeInfo::get<Vector2f>()) {
                const Vector2f value = material->getProperty2f( name );
                ::glUniform2f( uniformLocation, value.x, value.y);
            } else if (info == TypeInfo::get<Vector3f>()) {
                const Vector3f value = material->getProperty3f( name );
                ::glUniform3f( uniformLocation, value.x, value.y, value.z );
            } else if (info == TypeInfo::get<Vector4f>() ) {
                const Vector4f value = material->getProperty4f(name);
                ::glUniform4f( uniformLocation, value.x, value.y, value.z, value.w );
            } else {
                // TODO: Throw exception for unsupported type.
            }
        }
    }
    
    GL3_CHECK();
}


void GL3GraphicsDriver::postRenderMaterial(const Material *material) {
    const MaterialLayer *layer = nullptr;
    const GL3Texture *texture = nullptr;
    GLenum textureType = 0;
    
    for (int i=0; i<material->getLayerCount(); ++i) {
        if (layer->hasTexture() == true) {
            texture = static_cast<const GL3Texture*>(layer->getTexture());
            textureType = convTextureType(texture->getType());
            
            ::glActiveTexture(GL_TEXTURE0 + i);
            ::glBindTexture(textureType, 0);
        }
    }
    
    GL3_CHECK();
}

void GL3GraphicsDriver::updateTransforms() {
    const GLint programId = this->shaderProgram->getProgramId();
    
    // TODO: Remove the magic number '3'
    for (int i=0; i<3; ++i) {
        const std::string &name = this->transformNames[i];
        const Matrix4f &matrix  = this->transforms[i];
        
        const GLint location = ::glGetUniformLocation(programId, name.c_str());
        
        if (location != -1) {
            ::glUniformMatrix4fv(location, 1, GL_FALSE, matrix.getPtr());
        }
    }
    
    GL3_CHECK();
}

void GL3GraphicsDriver::raiseEvent(EventData &data) {
    for ( IEventHandler *handler : this->eventHandlers ) {
        handler->handleEvent(data);
    }
}

}}}
