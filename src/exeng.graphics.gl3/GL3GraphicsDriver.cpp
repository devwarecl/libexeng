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
#include "GL3IndexBuffer.hpp"
#include "GL3Shader.hpp"
#include "GL3ShaderProgram.hpp"
#include "GL3MeshSubset.hpp"

#include <exeng/DataType.hpp>
#include <exeng/input/IEventHandler.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/Material.hpp>

#include <map>

using namespace exeng;
using namespace exeng::graphics;
using namespace exeng::input;

namespace exeng { namespace graphics { namespace gl3 {

    // TODO: Add the specific transformation variables
    static const std::string defaultVSSource = std::string (
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

    static const std::string defaultFSSource = std::string (
        "#version 330 \n"
        "in vec2 uv; \n"
        "out vec4 outputColor; \n"
        "uniform sampler2D texSampler2D; \n"
        "void main() { \n"
        "outputColor = texture(texSampler2D, uv); \n"
        "}\n"
    );

    static void closeEvent(GLFWwindow *window) 
    {
        auto *plugin = exeng::graphics::gl3::currentPlugin;
        
        CloseEventData closeEventData(CloseReason::Unknown);
        
        plugin->getFactory()->getGraphicsDriver(window)->raiseEvent(closeEventData);
    }
    
    static void keyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) 
    {
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

    GL3GraphicsDriver::GL3GraphicsDriver() {}

    GL3GraphicsDriver::~GL3GraphicsDriver() 
    {
        this->terminate();
    }

    void GL3GraphicsDriver::initialize() 
    {
        this->initialize(DisplayMode());
    }

    void GL3GraphicsDriver::initialize(const DisplayMode &displayMode) 
    {
        if (initializedCount > 0) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::initialize: ";
            msg += "Only a single GL3 graphics driver can be initialized at time";
            
            throw std::runtime_error(msg);
        }
        
        // Configure and create the context
        this->context = std::auto_ptr<GL3Context>(new GL3Context());

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
        
        this->context->window = ::glfwCreateWindow(width, height, "exeng-graphics-gl3 Window", monitor, NULL);
        if (this->context->window == nullptr) {
            throw std::runtime_error("GL3GraphicsDriver::GL3GraphicsDriver: Cannot create a GLFW Window.");
        }
        
        ::glfwMakeContextCurrent(this->context->window);
        
        // Set the 
        ::glfwSetWindowCloseCallback(this->context->window, closeEvent);
        ::glfwSetKeyCallback(this->context->window, keyEvent);

        this->setTransformName(Transform::World, "WorldTransform");
        this->setTransformName(Transform::View, "ViewTransform");
        this->setTransformName(Transform::Projection, "ProjectionTransform");
        
        // Initialize the OpenGL 3 core functions
        ::ogl_LoadFunctions();
        
        // Default vertex shader
        std::unique_ptr<Shader> vertexShader = this->createShader(ShaderType::Vertex);
        
        vertexShader->setSourceCode(defaultVSSource);
        vertexShader->compile();
        
        // Default pixel shader
        std::unique_ptr<Shader> fragmentShader = this->createShader(ShaderType::Fragment);
        
        fragmentShader->setSourceCode(defaultFSSource);
        fragmentShader->compile();
        
        // Default shader program
        std::unique_ptr<ShaderProgram> shaderProgram = this->createShaderProgram();
        
        shaderProgram->addShader(std::move(vertexShader));
        shaderProgram->addShader(std::move(fragmentShader));
        shaderProgram->link();
        
        // Hold all the default objects
        this->defaultProgram = std::move(shaderProgram);
        
        this->displayMode = displayMode;
        
        this->initialized = true;
        ++GL3GraphicsDriver::initializedCount;
    }

    void GL3GraphicsDriver::terminate() 
    {
        if (this->initialized == true) {
            --GL3GraphicsDriver::initializedCount;
            
            /*
            delete this->defaultMaterial.release();
            delete this->defaultProgram.release();
            delete this->defaultVertexShader.release();
            delete this->defaultFragmentShader.release();

            //! TODO: Destroy all created objects
            ::glfwDestroyWindow(this->context->window);
            ::glfwTerminate();
            this->context->window = nullptr;
            this->initialized = false;
            */
        }
    }

    bool GL3GraphicsDriver::isInitialized() const 
    {
        return this->initialized;
    }

    void GL3GraphicsDriver::beginFrame(const Vector4f &color, ClearFlags::Flags flags) 
    {
#if defined(EXENG_DEBUG)
        if (this->renderingFrame == true) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::beginFrame: ";
            msg += "Can't rendering a new frame if the current one hasn't been completed.";
            
            throw std::logic_error(msg);
        }       
#endif
        GLenum clearFlags = 0L;
        clearFlags |= flags.isActivated(ClearFlags::Color)?GL_COLOR_BUFFER_BIT:0;
        clearFlags |= flags.isActivated(ClearFlags::Depth)?GL_DEPTH_BUFFER_BIT:0;
        clearFlags |= flags.isActivated(ClearFlags::Stencil)?GL_STENCIL_BUFFER_BIT:0;
        
#if defined(EXENG_DEBUG)
        if (!clearFlags) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::beginScene: ";
            msg += "Flags must be non 0.";
            
            throw std::invalid_argument(msg);
        }
#endif  
        ::glClearColor(color.x, color.y, color.z, color.w);
        ::glClear(clearFlags);
        
        this->renderingFrame = true;
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::endFrame() 
    {
#if defined(EXENG_DEBUG)
        if (this->renderingFrame == false) {
            std::string msg;
            
            msg += "GL3GraphicsDriver::endFrame: ";
            msg += "Invalid call because must start a new frame first, via the beginFrame method.";
            
            throw std::logic_error(msg);
        }
#endif
        ::glFinish();
        ::glfwSwapBuffers(this->context->window);
        
        this->renderingFrame = false;
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::setMeshSubset(MeshSubset *meshSubset) 
    {
#if defined(EXENG_DEBUG)
        if (meshSubset->getTypeInfo() != TypeId<GL3MeshSubset>()) {
            throw std::runtime_error("GL3GraphicsDriver::setMeshSubset: Invalid meshSubset TypeInfo.");
        }

        for (int i=0; i<meshSubset->getBufferCount(); ++i) {
            if (meshSubset->getBuffer(i)->getTypeInfo() != TypeId<GL3Buffer>()) {
                throw std::runtime_error("GL3GraphicsDriver::setMeshSubset: Invalid vertex buffer TypeInfo.");
            }
        }

        //  
        if (meshSubset->getIndexBuffer() && (meshSubset->getIndexBuffer()->getTypeInfo() != TypeId<GL3Buffer>())) {
            throw std::runtime_error("GL3GraphicsDriver::setMeshSubset: Invalid index buffer TypeInfo.");
        }
#endif
        if (meshSubset->getBufferCount() != 1) {
            throw std::runtime_error("GL3GraphicsDriver::setMeshSubset: Only one vertex buffer is supported for now");
        }
        
        this->meshSubset = static_cast<GL3MeshSubset*>(meshSubset);
        this->vertexBuffer = static_cast<GL3Buffer*>(meshSubset->getBuffer(0));
        this->indexBuffer = static_cast<GL3Buffer*>(meshSubset->getIndexBuffer());

        VertexFormat format = this->meshSubset->getVertexFormat();
        int baseAttrib = 0;
        int offset = 0;
        DataType::Enum dataTypeKey;
        
        ::glBindVertexArray( this->meshSubset->getVertexArrayId());
        ::glBindBuffer( GL_ARRAY_BUFFER, this->vertexBuffer->getBufferId() );
        
        for (const VertexField& field : format.fields) {
            if (field.attribute == VertexAttrib::Unused) {
                break;
            }
            
            dataTypeKey = field.dataType;
            GLenum dataType = convDataType(dataTypeKey);
            
            ::glEnableVertexAttribArray(baseAttrib);
            ::glVertexAttribPointer(baseAttrib, field.count, 
                                    dataType, GL_FALSE, format.getSize(), 
                                    reinterpret_cast<const void*>(offset));
            
            offset += field.count * DataType::getSize(field.dataType);
            ++baseAttrib;
        }
        
        GL3_CHECK();

    }

    MeshSubset* GL3GraphicsDriver::getMeshSubset() 
    {
        return this->meshSubset;
    }

    const MeshSubset* GL3GraphicsDriver::getMeshSubset() const 
    {
        return this->meshSubset;
    }

    void GL3GraphicsDriver::setMaterial(const Material* material) 
    {
#if defined (EXENG_DEBUG)
		// Check for a default material first
		if (!this->defaultMaterial) {
			throw std::runtime_error("GL3GraphicsDriver::preRenderMaterial: No default material available.");
		}

        // Check texture type info
        if (material && material->checkTextureType(TypeId<GL3Texture>()) == false) {
            throw std::runtime_error("GL3GraphicsDriver::setMaterial: The supplied texture class implementation must be GL3Texture.");
        }
            
        // Check if the  textures were created by this GL3GraphicsDriver.
        // const int layerCount = material->getLayerCount();
        // const MaterialLayer *layer = nullptr;
        // for (int i=0; i<layerCount; ++i) {
        //     layer = material->getLayer(i);
        //    
        //     if (layer->hasTexture() == true && layer->getTexture()->getResourceManager() != this) {
        //         std::string msg;
        //        
        //         msg += "GL3GraphicsDriver::setMaterial: ";
        //         msg += "The textures used by this material are not valid.";
        //        
        //         throw std::logic_error(msg);
        //     }
        // }
        
        // Check for shader program info and status
        if (material && material->getShaderProgram() != nullptr ) {
            if ( material->getShaderProgram()->getTypeInfo() != TypeId<GL3ShaderProgram>() ) {
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

    std::unique_ptr<Buffer> GL3GraphicsDriver::createVertexBuffer(const std::int32_t size, const void* data) 
    {
        auto vertexBuffer = std::unique_ptr<Buffer>(new GL3Buffer(GL_ARRAY_BUFFER, size));

        if (data) {
            vertexBuffer->setData(data, size);
        }

        return vertexBuffer;
    }

    std::unique_ptr<Buffer> GL3GraphicsDriver::createIndexBuffer(const std::int32_t size, const void* data) 
    {
        auto vertexBuffer = std::unique_ptr<Buffer>(new GL3Buffer(GL_ARRAY_BUFFER, size));

        if (data) {
            vertexBuffer->setData(data, size);
        }

        return vertexBuffer;
    }

    std::unique_ptr<Texture> GL3GraphicsDriver::createTexture(TextureType::Enum type, const Vector3f& size, const ColorFormat &format) 
    {
        auto texture = std::unique_ptr<Texture>(new GL3Texture(type, size, format));
        // this->addResource(texture);
        
        return texture;
    }

    void GL3GraphicsDriver::setTransform(Transform::Enum transform, const Matrix4f& transformMatrix) 
    {
        const int index = static_cast<const int>(transform);
        this->transforms[index] = transformMatrix;
        
        this->updateTransforms();
    }

    void GL3GraphicsDriver::setViewport(const Rectf& viewport) 
    {
        auto minEdge = viewport.getMin();
        auto size = viewport.geSize();
        
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

    void GL3GraphicsDriver::render(Primitive::Enum ptype, int count) 
    {
#if defined(EXENG_DEBUG)
        if (this->vertexBuffer == nullptr) {
            throw std::runtime_error("GL3GraphicsDriver::render: A current binded vertex buffer must be setted.");
        }

        // Check if the current setted buffer is the same
        GLint bufferId = 0;
        ::glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferId);
        assert( bufferId != 0 );
        assert( bufferId == (GLint)this->vertexBuffer->getBufferId() );
#endif

        //! TODO: Implement rendering path with the index buffer in the future.
        GLenum primitive = convPrimitive(ptype);
        ::glDrawArrays(primitive, 0, count);
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::pollEvents() 
    {
        ::glfwPollEvents();
        
        //! TODO: notify the event handlers for events
    }

    void GL3GraphicsDriver::addEventHandler(IEventHandler *handler) 
    {
        this->eventHandlers.push_back(handler);
    }

    void GL3GraphicsDriver::removeEventHandler(IEventHandler *handler) 
    {
        this->eventHandlers.remove(handler);
    }

    void GL3GraphicsDriver::setDisplayMode(const DisplayMode &displayMode) 
    {
        throw std::runtime_error("GL3GraphicsDriver::setDisplayMode: Not implemented yet.");
    }

    DisplayMode GL3GraphicsDriver::getDisplayMode() const 
    {
        return this->displayMode;
    }

    void GL3GraphicsDriver::restoreDisplayMode() 
    {
        throw std::runtime_error("GL3GraphicsDriver::restoreDisplayMode: Not implemented yet.");
    }
    
    std::unique_ptr<Shader> GL3GraphicsDriver::createShader( ShaderType::Enum type ) 
    {
        auto shader = std::unique_ptr<Shader>(new GL3Shader(type));
        return shader;
    }

    std::unique_ptr<ShaderProgram> GL3GraphicsDriver::createShaderProgram()
    {
        auto shaderProgram = std::unique_ptr<ShaderProgram>(new GL3ShaderProgram());
        return shaderProgram;
    }
    
    typedef void (CODEGEN_FUNCPTR *__glUniformfv)(GLint, GLsizei, const GLfloat *);
    
    inline __glUniformfv getUniformFunction(int dimension) 
    {
        switch (dimension) {
            case 1: return glUniform1fv;
            case 2: return glUniform2fv;
            case 3: return glUniform3fv;
            case 4: return glUniform4fv;
			default: return nullptr;
        }
    }
    
    void GL3GraphicsDriver::preRenderMaterial(const Material *material) 
	{
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
            shaderProgram = static_cast<const GL3ShaderProgram*>(this->defaultProgram.get() );
        }
        
        GLint programId = shaderProgram->getProgramId();
        ::glUseProgram(programId);
        
        // Set material attributes
        GLint uniformLocation = 0;
        
        const MaterialFormat *materialFormat = material->getFormat();
        
        for(int i=0; i<materialFormat->getAttribCount(); ++i) {
            const MaterialAttrib &attrib = *materialFormat->getAttrib(i);
            
            uniformLocation = ::glGetUniformLocation(programId, attrib.name.c_str());
            
            if (uniformLocation <= -1) {
                continue;
            }
            
            if (attrib.dataType != DataType::Float32) {
                continue;
            }
            
            Vector4f value = material->getAttribute<Vector4f>(i);
            
            // __glUniformfv glUniformfv = getUniformFunction(attrib.dimension);
            // glUniformfv(uniformLocation, 1, value.data);

			getUniformFunction(attrib.dimension)(uniformLocation, 1, value.data);
        }
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::postRenderMaterial(const Material *material) 
    {
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

    void GL3GraphicsDriver::updateTransforms() 
    {
        const GLint programId = this->shaderProgram->getProgramId();
        const int transformCount = 3;
        
        for (int i=0; i<transformCount; ++i) {
            const std::string &name = this->transformNames[i];
            const Matrix4f &matrix  = this->transforms[i];
            
            const GLint location = ::glGetUniformLocation(programId, name.c_str());
            
            if (location != -1) {
                ::glUniformMatrix4fv(location, 1, GL_FALSE, matrix.getPtr());
            }
        }
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::raiseEvent(EventData &data) 
    {
        for (IEventHandler *handler : this->eventHandlers) {
            handler->handleEvent(data);
        }
    }

    std::unique_ptr<MeshSubset> GL3GraphicsDriver::createMeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers, std::unique_ptr<Buffer> indexBuffer, const VertexFormat &format) 
    {
        return std::unique_ptr<MeshSubset>(new GL3MeshSubset( std::move(vertexBuffers), std::move(indexBuffer), format));
    }

	void GL3GraphicsDriver::setDefaultMaterial(const Material *material) 
    {
		this->defaultMaterial = const_cast<Material*>(material);
        this->defaultMaterial->setShaderProgram(this->defaultProgram.get());
	}
}}}
