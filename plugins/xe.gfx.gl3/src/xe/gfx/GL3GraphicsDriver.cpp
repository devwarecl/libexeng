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
#include "GL3Shader.hpp"
#include "GL3ShaderProgram.hpp"
#include "GL3MeshSubset.hpp"

#include <xe/DataType.hpp>
#include <xe/Exception.hpp>
#include <xe/input/IEventHandler.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/Material.hpp>

#include <map>

using namespace xe;
using namespace xe::gfx;
using namespace xe::input;

namespace xe { namespace gfx { namespace gl3 {

	// 
	static std::map<GLFWwindow*, GL3GraphicsDriver*> drivers;

    static void closeEvent(GLFWwindow *window)
    {
		CloseEventData closeEventData(CloseReason::Unknown);
		xe::gfx::gl3::drivers[window]->raiseEvent(closeEventData);
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

        InputEventData inputEventData(status, code);
        
		xe::gfx::gl3::drivers[window]->raiseEvent(inputEventData);
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
            EXENG_THROW_EXCEPTION("Only a single GL3 graphics driver can be initialized at time");
        }
        
		if (this->initialized) {
			EXENG_THROW_EXCEPTION("Already initialized.");
		}

        // Configure and create the context
        auto context = std::make_unique<GL3Context>();

        GLFWmonitor *monitor = nullptr;
        
        switch (displayMode.status) {
            case DisplayStatus::Window: monitor = nullptr; break;
            case DisplayStatus::Fullscreen: monitor = ::glfwGetPrimaryMonitor() ; break;
        }
        
        ::glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        ::glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
		::glfwWindowHint(GLFW_DEPTH_BITS, 24);
		::glfwWindowHint(GLFW_DOUBLEBUFFER , GL_TRUE);

        int width = displayMode.size.width;
        int height = displayMode.size.height;
        
        context->window = ::glfwCreateWindow(width, height, "exeng-graphics-gl3 Window", monitor, NULL);
        if (context->window == nullptr) {
			EXENG_THROW_EXCEPTION("GL3GraphicsDriver::GL3GraphicsDriver: Cannot create a GLFW Window.");
        }
        
        ::glfwMakeContextCurrent(context->window);
        
        // Set the 
        ::glfwSetWindowCloseCallback(context->window, closeEvent);
        ::glfwSetKeyCallback(context->window, keyEvent);

        // Initialize the OpenGL 3 core functions
        ::ogl_LoadFunctions();
        
		// Configure OpenGL state
		::glEnable(GL_CULL_FACE);
		::glEnable(GL_DEPTH_TEST);
		::glDepthFunc(GL_LEQUAL);
		// ::glClearDepth(1.0f);

        // Hold all the default objects
		drivers[context->window] = this;
		this->context = std::move(context);
        this->displayMode = displayMode;
        this->initialized = true;

        ++GL3GraphicsDriver::initializedCount;

		GL3_CHECK();
    }

    void GL3GraphicsDriver::terminate() 
    {
        if (this->initialized == true) {
            --GL3GraphicsDriver::initializedCount;
			this->initialized = false;

			drivers.erase(this->context->window);
        }

		this->context.reset(nullptr);
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
            
            EXENG_THROW_EXCEPTION(msg);
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
            
            EXENG_THROW_EXCEPTION(msg);
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
            
            EXENG_THROW_EXCEPTION(msg);
        }
#endif
        ::glFinish();
        ::glfwSwapBuffers(this->context->window);
        
        this->renderingFrame = false;
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::setMeshSubset(const MeshSubset *meshSubset) {
#if defined(EXENG_DEBUG)
		assert(this);
		assert(meshSubset);
		assert(static_cast<const GL3MeshSubset*>(meshSubset)->getVertexArrayId());
		
        if (meshSubset->getTypeInfo() != TypeId<GL3MeshSubset>()) {
			EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMeshSubset: Invalid meshSubset TypeInfo.");
        }

        for (int i=0; i<meshSubset->getBufferCount(); ++i) {
            if (meshSubset->getBuffer(i)->getTypeInfo() != TypeId<GL3Buffer>()) {
                EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMeshSubset: Invalid vertex buffer TypeInfo.");
            }
        }

        //  
        if (meshSubset->getIndexBuffer() && (meshSubset->getIndexBuffer()->getTypeInfo() != TypeId<GL3Buffer>())) {
            EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMeshSubset: Invalid index buffer TypeInfo.");
        }

		if (meshSubset->getBufferCount() != 1) {
            EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMeshSubset: Only one vertex buffer is supported for now");
        }
#endif
        this->meshSubset = static_cast<const GL3MeshSubset*>(meshSubset);
        this->vertexBuffer = static_cast<const GL3Buffer*>(meshSubset->getBuffer(0));
        this->indexBuffer = static_cast<const GL3Buffer*>(meshSubset->getIndexBuffer());

		const GLuint vertexArrayId = this->meshSubset->getVertexArrayId();
		::glBindVertexArray(vertexArrayId);

#if defined(EXENG_DEBUG)
		xe::gfx::gl3::checkMeshSubsetBinding(this->meshSubset);
#endif

		char buffer[65536] = {0};

        GL3_CHECK();
    }
    
    const MeshSubset* GL3GraphicsDriver::getMeshSubset() const {
        return this->meshSubset;
    }

    void GL3GraphicsDriver::setMaterial(const Material* material) {
#if defined (EXENG_DEBUG)

		if (!material) {
			EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMaterial: The supplied material can't be null.");
		}

        // Check texture type info
        if (material && material->checkTextureType(TypeId<GL3Texture>()) == false) {
            EXENG_THROW_EXCEPTION("GL3GraphicsDriver::setMaterial: The supplied texture class implementation must be GL3Texture.");
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
        //         EXENG_THROW_EXCEPTION(msg);
        //     }
        // }
        
        // Check for shader program info and status
        if (material && material->getShaderProgram() != nullptr ) {
            if ( material->getShaderProgram()->getTypeInfo() != TypeId<GL3ShaderProgram>() ) {
                std::string msg;
                
                msg += "GL3GraphicsDriver::setMaterial: ";
                msg += "Expected a shader program of type GL3ShaderProgram";
                
                EXENG_THROW_EXCEPTION(msg);
            }
            
            if ( material->getShaderProgram()->isLinked() == false ) {
                std::string msg;
                
                msg += "GL3GraphicsDriver::setMaterial: ";
                msg += "The shader program must be linked by client code.";
                
                EXENG_THROW_EXCEPTION(msg);
            }
        }
#endif
        if (this->material != nullptr && this->material != material) {
            this->postRenderMaterial(this->material);
        }
        
        this->preRenderMaterial(material);
        this->material = material;
    }

    std::unique_ptr<Buffer> GL3GraphicsDriver::createVertexBuffer(const std::int32_t size, const void* data) 
    {
        auto vertexBuffer = std::unique_ptr<Buffer>(new GL3Buffer(size, GL_ARRAY_BUFFER));

        if (data) {
            vertexBuffer->setData(data);
        }

        return vertexBuffer;
    }

    std::unique_ptr<Buffer> GL3GraphicsDriver::createIndexBuffer(const std::int32_t size, const void* data) 
    {
        auto vertexBuffer = std::unique_ptr<Buffer>(new GL3Buffer(size, GL_ELEMENT_ARRAY_BUFFER));

        if (data) {
            vertexBuffer->setData(data);
        }

        return vertexBuffer;
    }

    TexturePtr GL3GraphicsDriver::createTexture(const Vector2i& size, const ColorFormat &format, const void* data) 
    {
		TexturePtr texture = std::make_unique<GL3Texture>(TextureType::Tex2D, (Vector3i)size, format, data);

        return texture;
    }

	TexturePtr GL3GraphicsDriver::createTexture(const Vector3i& size, const ColorFormat &format, const void* data) 
    {
		TexturePtr texture = std::make_unique<GL3Texture>(TextureType::Tex3D, size, format, data);

        return texture;
    }

	TexturePtr GL3GraphicsDriver::createTextureCube(const Vector2i& size, const ColorFormat &format, const void* data) 
    {
		TexturePtr texture = std::make_unique<GL3Texture>(TextureType::TexCubeMap, (Vector3i)size, format, data);

        return texture;
    }

    void GL3GraphicsDriver::setViewport(const Rectf& viewport) 
    {
        const auto minEdge = static_cast<Vector2i>(viewport.getMin());
        const auto size = static_cast<Size2i>(viewport.getSize());

        ::glViewport (
			minEdge.x, 
			minEdge.y, 
			size.width, 
			size.height==0 ? 1 : size.height
		);

		this->viewport = viewport;
        GL3_CHECK();
    }

    void GL3GraphicsDriver::render(Primitive::Enum ptype, int count) {
#if defined(EXENG_DEBUG)
		xe::gfx::gl3::checkMeshSubsetBinding(this->meshSubset);
#endif
        GLenum primitive = convPrimitive(ptype);

		// Normal render
		if (!this->indexBuffer) {
			::glDrawArrays(primitive, 0, count);
		} else {
			const IndexFormat::Enum indexFormat = this->meshSubset->getIndexFormat();
			const GLuint dataType = convIndexFormatType(indexFormat);
			const int indexCount = this->meshSubset->getIndexCount();

			::glDrawElements(primitive, indexCount, dataType, nullptr);
		}
        
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

    DisplayMode GL3GraphicsDriver::getDisplayMode() const 
    {
        return this->displayMode;
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
    
    void GL3GraphicsDriver::preRenderMaterial(const Material *material) {
        assert(material != nullptr);
        
        // set the texture state
        for(int i=0; i<material->getLayerCount(); ++i) {
            const MaterialLayer *layer = material->getLayer(i);
            
            if (layer->hasTexture() == true) {
                const GL3Texture *texture = static_cast<const GL3Texture*>(layer->getTexture());
                GLenum textureType = convTextureType(texture->getType());
                GLenum textureId = texture->getTextureId();
                
                ::glActiveTexture(GL_TEXTURE0 + i);
                ::glBindTexture(textureType, textureId);
            }
        }
        
        // set the shader program state
        const GL3ShaderProgram *shaderProgram = static_cast<const GL3ShaderProgram *>(material->getShaderProgram());
        
        GLint programId = shaderProgram->getProgramId();
        ::glUseProgram(programId);
        
        if (material->getFormat()) {
            // Set material attributes
            const MaterialFormat *materialFormat = material->getFormat();
            
            for(int i=0; i<materialFormat->getAttribCount(); ++i) {
                const MaterialAttrib &attrib = *materialFormat->getAttrib(i);
                const GLint uniformLocation = ::glGetUniformLocation(programId, attrib.name.c_str());
                
                if (uniformLocation <= -1) {
                    continue;
                }
                
                if (attrib.dataType != DataType::Float32) {
                    continue;
                }
                
                Vector4f value = material->getAttribute<Vector4f>(i);

                getUniformFunction(attrib.dimension)(uniformLocation, 1, value.data);
            }
        }
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::postRenderMaterial(const Material *material) {

        for (int i=0; i<material->getLayerCount(); ++i) {
			const MaterialLayer *layer = material->getLayer(i);

            if (layer->hasTexture() == true) {
                const GL3Texture *texture = static_cast<const GL3Texture*>(layer->getTexture());
                GLenum textureType = convTextureType(texture->getType());
                
                ::glActiveTexture(GL_TEXTURE0 + i);
                ::glBindTexture(textureType, 0);
            }
        }
        
        GL3_CHECK();
    }

    void GL3GraphicsDriver::raiseEvent(EventData &data)  {
        for (IEventHandler *handler : this->eventHandlers) {
            handler->handleEvent(data);
        }
    }

    std::unique_ptr<MeshSubset> GL3GraphicsDriver::createMeshSubset(std::vector<std::unique_ptr<Buffer>> vertexBuffers, std::unique_ptr<Buffer> indexBuffer, const VertexFormat &format) {
		return std::unique_ptr<MeshSubset>(new GL3MeshSubset(std::move(vertexBuffers), format, std::move(indexBuffer), IndexFormat::Index32));
    }

	void GL3GraphicsDriver::setProgramGlobal(const std::string &globalName, const Vector4f &value) {
#if defined(EXENG_DEBUG)
		if (!this->getMaterial()) {
			EXENG_THROW_EXCEPTION("No current material bound.");
		}

		if (!this->getMaterial()->getShaderProgram()) {
			EXENG_THROW_EXCEPTION("No current shader program bound.");
		}
#endif
		const GL3ShaderProgram *shaderProgram = this->getShaderProgram();

		int programId = shaderProgram->getProgramId();
		int location = glGetUniformLocation(programId, globalName.c_str());

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform variable '" + globalName + "' doesn't exist in the current program.");
		}
#endif
		glUniform4fv(location, 1, value.getPtr());

		GL3_CHECK();
	}

	void GL3GraphicsDriver::setProgramGlobal(const std::string &globalName, const Matrix4f &value) {
#if defined(EXENG_DEBUG)
		if (!this->getMaterial()) {
			EXENG_THROW_EXCEPTION("No current material bound.");
		}

		if (!this->getMaterial()->getShaderProgram()) {
			EXENG_THROW_EXCEPTION("No current shader program bound.");
		}
#endif
		const GL3ShaderProgram *shaderProgram = this->getShaderProgram();

		int programId = shaderProgram->getProgramId();
		int location = glGetUniformLocation(programId, globalName.c_str());

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform variable '" + globalName + "' doesn't exist in the current program.");
		}
#endif
		glUniformMatrix4fv(location, 1, GL_FALSE, value.getPtr());

		GL3_CHECK();
	}

	void GL3GraphicsDriver::setProgramGlobal(const int index, const Vector4f &value) {
#if defined(EXENG_DEBUG)
		if (!this->getMaterial()) {
			EXENG_THROW_EXCEPTION("No current material bound.");
		}

		if (!this->getMaterial()->getShaderProgram()) {
			EXENG_THROW_EXCEPTION("No current shader program bound.");
		}
#endif
		const GL3ShaderProgram *shaderProgram = this->getShaderProgram();

		int programId = shaderProgram->getProgramId();
		int location = index;

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform index '" + std::to_string(index) + "' doesn't exist in the current program.");
		}
#endif
		glUniform4fv(location, 1, value.getPtr());

		GL3_CHECK();
	}

	void GL3GraphicsDriver::setProgramGlobal(const int index, const Matrix4f &value) {
#if defined(EXENG_DEBUG)
		if (!this->getMaterial()) {
			EXENG_THROW_EXCEPTION("No current material bound.");
		}

		if (!this->getMaterial()->getShaderProgram()) {
			EXENG_THROW_EXCEPTION("No current shader program bound.");
		}
#endif
		const GL3ShaderProgram *shaderProgram = this->getShaderProgram();

		int programId = shaderProgram->getProgramId();
		int location = index;

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform variable '" + std::to_string(index)  + "' doesn't exist in the current program.");
		}
#endif
		glUniformMatrix4fv(location, 1, GL_FALSE, value.getPtr());

		GL3_CHECK();
	}

	ModernModule* GL3GraphicsDriver::getModernModule() {
		return this;
	}
}}}
