/**
 * @file GraphicsDriverGL3.cpp
 * @brief Implementation of the GL3 Graphics Driver class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "UtilGL3.hpp"
#include <GLFW/glfw3.h>

#include "GraphicsDriverGL3.hpp"
#include "PluginGL3.hpp"
#include "GraphicsDriverFactoryGL3.hpp"
#include "DebugGL3.hpp"
#include "ShaderGL3.hpp"
#include "TextureGL3.hpp"
#include "ShaderGL3.hpp"
#include "ShaderProgramGL3.hpp"
#include "MeshSubsetGL3.hpp"

#include <xe/DataType.hpp>
#include <xe/Exception.hpp>
#include <xe/input/IEventHandler.hpp>
#include <xe/gfx/VertexFormat.hpp>
#include <xe/gfx/Material.hpp>

#include <map>

using namespace xe;
using namespace xe::gfx;
using namespace xe::input2;

namespace xe { namespace gfx { namespace gl3 {

    int GraphicsDriverGL3::initializedCount = 0;

    GraphicsDriverGL3::GraphicsDriverGL3() {}

    GraphicsDriverGL3::~GraphicsDriverGL3() {
        this->terminate();
    }

    void GraphicsDriverGL3::initialize() {
        this->initialize(DisplayMode());
    }

    void GraphicsDriverGL3::initialize(const DisplayMode &displayMode) {
        if (initializedCount > 0) {
            EXENG_THROW_EXCEPTION("Only a single GL3 graphics driver can be initialized at time");
        }
        
		if (this->initialized) {
			EXENG_THROW_EXCEPTION("Already initialized.");
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
		::glfwWindowHint(GLFW_DEPTH_BITS, 24);
		::glfwWindowHint(GLFW_DOUBLEBUFFER , GL_TRUE);

        int width = displayMode.size.x;
        int height = displayMode.size.y;
        
        GLFWwindow *window = ::glfwCreateWindow(width, height, "exeng-graphics-gl3 Window", monitor, NULL);
        
        if (!window) {
			EXENG_THROW_EXCEPTION("GraphicsDriverGL3::GraphicsDriverGL3: Cann't create a GLFW Window.");
        }
        
        ::glfwMakeContextCurrent(window);
        
        // Initialize the OpenGL 3 core functions
        ::ogl_LoadFunctions();
        
		// Configure OpenGL state
		::glEnable(GL_CULL_FACE);
		::glEnable(GL_DEPTH_TEST);
		::glDepthFunc(GL_LEQUAL);
		// ::glClearDepth(1.0f);

		// Link the current input manager
		::glfwSetWindowUserPointer(window, this);
		this->inputManager.setWindow(window); 

        // Hold all the default objects
        this->context.window = window;
        this->displayMode = displayMode;
        this->initialized = true;
		
        ++GraphicsDriverGL3::initializedCount;

		GL3_CHECK();
    }

    void GraphicsDriverGL3::terminate() 
    {
        if (this->initialized == true) {
            --GraphicsDriverGL3::initializedCount;
			this->initialized = false;
        }

		this->context.~Context();
    }

    bool GraphicsDriverGL3::isInitialized() const {
        return this->initialized;
    }

    void GraphicsDriverGL3::beginFrame(const Vector4f &color, ClearFlags::Flags flags) 
    {
#if defined(EXENG_DEBUG)
        if (this->renderingFrame == true) {
            std::string msg;
            
            msg += "GraphicsDriverGL3::beginFrame: ";
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
            
            msg += "GraphicsDriverGL3::beginScene: ";
            msg += "Flags must be non 0.";
            
            EXENG_THROW_EXCEPTION(msg);
        }
#endif  
        ::glClearColor(color.x, color.y, color.z, color.w);
        ::glClear(clearFlags);
        
        this->renderingFrame = true;
        
        GL3_CHECK();
    }

    void GraphicsDriverGL3::endFrame() 
    {
#if defined(EXENG_DEBUG)
        if (this->renderingFrame == false) {
            std::string msg;
            
            msg += "GraphicsDriverGL3::endFrame: ";
            msg += "Invalid call because must start a new frame first, via the beginFrame method.";
            
            EXENG_THROW_EXCEPTION(msg);
        }
#endif
        ::glFinish();
        ::glfwSwapBuffers(context.window);
        
        this->renderingFrame = false;
        
        GL3_CHECK();
    }

    void GraphicsDriverGL3::setMeshSubset(const MeshSubset *meshSubset) {
#if defined(EXENG_DEBUG)
		assert(this);
		assert(meshSubset);
		assert(static_cast<const MeshSubsetGL3*>(meshSubset)->getVertexArrayId());
		
        if (meshSubset->getTypeInfo() != TypeId<MeshSubsetGL3>()) {
			EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMeshSubset: Invalid meshSubset TypeInfo.");
        }

        for (int i=0; i<meshSubset->getBufferCount(); ++i) {
            if (meshSubset->getBuffer(i)->getTypeInfo() != TypeId<BufferGL3>()) {
                EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMeshSubset: Invalid vertex buffer TypeInfo.");
            }
        }

        //  
        if (meshSubset->getIndexBuffer() && (meshSubset->getIndexBuffer()->getTypeInfo() != TypeId<BufferGL3>())) {
            EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMeshSubset: Invalid index buffer TypeInfo.");
        }

		if (meshSubset->getBufferCount() != 1) {
            EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMeshSubset: Only one vertex buffer is supported for now");
        }
#endif
        this->meshSubset = static_cast<const MeshSubsetGL3*>(meshSubset);
        this->vertexBuffer = static_cast<const BufferGL3*>(meshSubset->getBuffer(0));
        this->indexBuffer = static_cast<const BufferGL3*>(meshSubset->getIndexBuffer());

		const GLuint vertexArrayId = this->meshSubset->getVertexArrayId();
		::glBindVertexArray(vertexArrayId);

#if defined(EXENG_DEBUG)
		xe::gfx::gl3::checkMeshSubsetBinding(this->meshSubset);
#endif

        GL3_CHECK();
    }
    
    const MeshSubset* GraphicsDriverGL3::getMeshSubset() const {
        return this->meshSubset;
    }

    void GraphicsDriverGL3::setMaterial(const Material* material) {
#if defined (EXENG_DEBUG)

		if (!material) {
			EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMaterial: The supplied material can't be null.");
		}

        // Check texture type info
        if (material && material->checkTextureType(TypeId<TextureGL3>()) == false) {
            EXENG_THROW_EXCEPTION("GraphicsDriverGL3::setMaterial: The supplied texture class implementation must be TextureGL3.");
        }
		
        // Check if the  textures were created by this GraphicsDriverGL3.
        // const int layerCount = material->getLayerCount();
        // const MaterialLayer *layer = nullptr;
        // for (int i=0; i<layerCount; ++i) {
        //     layer = material->getLayer(i);
        //    
        //     if (layer->hasTexture() == true && layer->getTexture()->getResourceManager() != this) {
        //         std::string msg;
        //        
        //         msg += "GraphicsDriverGL3::setMaterial: ";
        //         msg += "The textures used by this material are not valid.";
        //        
        //         EXENG_THROW_EXCEPTION(msg);
        //     }
        // }
        
        //// Check for shader program info and status
        //if (material && material->getShaderProgram() != nullptr ) {
        //    if ( material->getShaderProgram()->getTypeInfo() != TypeId<ShaderProgramGL3>() ) {
        //        std::string msg;
        //        
        //        msg += "GraphicsDriverGL3::setMaterial: ";
        //        msg += "Expected a shader program of type ShaderProgramGL3";
        //        
        //        EXENG_THROW_EXCEPTION(msg);
        //    }
        //    
        //    if ( material->getShaderProgram()->isLinked() == false ) {
        //        std::string msg;
        //        
        //        msg += "GraphicsDriverGL3::setMaterial: ";
        //        msg += "The shader program must be linked by client code.";
        //        
        //        EXENG_THROW_EXCEPTION(msg);
        //    }
        //}
#endif
        if (this->material != nullptr && this->material != material) {
            this->postRenderMaterial(this->material);
        }
        
        this->preRenderMaterial(material);
        this->material = material;
    }

    std::unique_ptr<Buffer> GraphicsDriverGL3::createVertexBuffer(const std::int32_t size, const void* data) 
    {
        auto vertexBuffer = std::unique_ptr<Buffer>(new BufferGL3(size, GL_ARRAY_BUFFER));

        if (data) {
            vertexBuffer->write(data);
        }

        return vertexBuffer;
    }

    std::unique_ptr<Buffer> GraphicsDriverGL3::createIndexBuffer(const std::int32_t size, const void* data) {
        auto vertexBuffer = std::unique_ptr<Buffer>(new BufferGL3(size, GL_ELEMENT_ARRAY_BUFFER));

        if (data) {
            vertexBuffer->write(data);
        }

        return vertexBuffer;
    }

    TexturePtr GraphicsDriverGL3::createTexture(const Vector2i& size, PixelFormat::Enum format, const void* data) {
		TexturePtr texture = std::make_unique<TextureGL3>(TextureType::Tex2D, (Vector3i)size, format, data);

        return texture;
    }

	TexturePtr GraphicsDriverGL3::createTexture(const Vector3i& size, PixelFormat::Enum format, const void* data) {
		TexturePtr texture = std::make_unique<TextureGL3>(TextureType::Tex3D, size, format, data);

        return texture;
    }

	TexturePtr GraphicsDriverGL3::createTextureCube(const Vector2i& size, PixelFormat::Enum format, const void* data) {
		TexturePtr texture = std::make_unique<TextureGL3>(TextureType::TexCubeMap, (Vector3i)size, format, data);

        return texture;
    }

    void GraphicsDriverGL3::setViewport(const Rectf& viewport) {
        const Vector2i minEdge = viewport.getMinEdge();
		const Vector2i size = viewport.getSize();

        ::glViewport (
			minEdge.x, 
			minEdge.y, 
			size.x, 
			size.y==0 ? 1 : size.y
		);

		this->viewport = viewport;
        GL3_CHECK();
    }

    void GraphicsDriverGL3::render(Primitive::Enum ptype, int count) {
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

    DisplayMode GraphicsDriverGL3::getDisplayMode() const 
    {
        return this->displayMode;
    }

    std::unique_ptr<Shader> GraphicsDriverGL3::createShader( ShaderType::Enum type ) 
    {
        auto shader = std::unique_ptr<Shader>(new ShaderGL3(type));
        return shader;
    }

    std::unique_ptr<ShaderProgram> GraphicsDriverGL3::createShaderProgram()
    {
        auto shaderProgram = std::unique_ptr<ShaderProgram>(new ShaderProgramGL3());
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
    
    void GraphicsDriverGL3::preRenderMaterial(const Material *material) {
        assert(material);
		assert(shaderProgram);

		GLuint programId = this->shaderProgram->getProgramId();

        // set the texture state
        for(int i=0; i<material->getLayerCount(); ++i) {
            const MaterialLayer *layer = material->getLayer(i);
            
            if (layer->hasTexture() == true) {
                const TextureGL3 *texture = static_cast<const TextureGL3*>(layer->getTexture());
                GLenum textureType = convTextureType(texture->getType());
                GLenum textureId = texture->getTextureId();
				
                GLuint textureLocation = ::glGetUniformLocation(programId, material->getFormat()->getLayerName(i).c_str());
                GL3_CHECK();

                ::glUniform1i(textureLocation, i);
                GL3_CHECK();

                ::glActiveTexture(GL_TEXTURE0 + i);
                GL3_CHECK();

                ::glBindTexture(textureType, textureId);
            }
        }
        
        GL3_CHECK();

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

    void GraphicsDriverGL3::postRenderMaterial(const Material *material) {

        for (int i=0; i<material->getLayerCount(); ++i) {
			const MaterialLayer *layer = material->getLayer(i);

            if (layer->hasTexture() == true) {
                const TextureGL3 *texture = static_cast<const TextureGL3*>(layer->getTexture());
                GLenum textureType = convTextureType(texture->getType());
                
                ::glActiveTexture(GL_TEXTURE0 + i);
                ::glBindTexture(textureType, 0);
            }
        }
        
        GL3_CHECK();
    }

    MeshSubsetPtr GraphicsDriverGL3::createMeshSubset(std::vector<BufferPtr> vertexBuffers, const VertexFormat *format, BufferPtr indexBuffer, IndexFormat::Enum iformat) {
		MeshSubsetPtr subset;

		subset = std::make_unique<MeshSubsetGL3>(std::move(vertexBuffers), format, std::move(indexBuffer), iformat);

		return subset;
    }

	ModernModule* GraphicsDriverGL3::getModernModule() {
		return this;
	}
	
	intptr_t GraphicsDriverGL3::getGLContext() const {
		return context.getGLContext();
	}

	intptr_t GraphicsDriverGL3::getOSContext() const {
		return context.getOSContext();
	}

	void GraphicsDriverGL3::setShaderProgram(const ShaderProgram *program) {
		shaderProgram = static_cast<const ShaderProgramGL3*>(program);
     
		if (shaderProgram) {
			GLint programId = shaderProgram->getProgramId();
			::glUseProgram(programId);
		} else {
			::glUseProgram(0);
		}
	}

	void GraphicsDriverGL3::setProgramMatrix(const std::string &name, const int count, const xe::Matrix4f *matrices) {
		assert(matrices);
		assert(count > 0);
		assert(shaderProgram);

		int programId = shaderProgram->getProgramId();
		int location = glGetUniformLocation(programId, name.c_str());

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform variable '" + name  + "' doesn't exist in the current program.");
		}
#endif
		glUniformMatrix4fv(location, count, GL_FALSE, matrices->getPtr());

		GL3_CHECK();
	}

	void GraphicsDriverGL3::setProgramParam(const std::string &name, const int count, const int dim, DataType::Enum dataType, const void *values) {
		assert(values);
		assert(count > 0);
		assert(dim > 0);
		assert(dim <= 4);
		assert(dataType == DataType::Float32);
		assert(dataType == DataType::Int32);
		assert(shaderProgram);

		int programId = shaderProgram->getProgramId();
		int location = glGetUniformLocation(programId, name.c_str());

#if defined(EXENG_DEBUG)
		if (location < 0) {
			EXENG_THROW_EXCEPTION("The uniform index '" + name + "' doesn't exist in the current program.");
		}
#endif

		auto fvalues = static_cast<const GLfloat*>(values);
		auto ivalues = static_cast<const GLint*>(values);

		switch (dataType) {
		case DataType::Float32:
			switch (dim) {
				case 1: glUniform1fv(location, count, fvalues); break;
				case 2: glUniform2fv(location, count, fvalues); break;
				case 3: glUniform3fv(location, count, fvalues); break;
				case 4: glUniform4fv(location, count, fvalues); break;
			}
			break;

		case DataType::Int32:
			switch (dim) {
				case 1: glUniform1iv(location, count, ivalues); break;
				case 2: glUniform2iv(location, count, ivalues); break;
				case 3: glUniform3iv(location, count, ivalues); break;
				case 4: glUniform4iv(location, count, ivalues); break;
			}
			break;
		}

		GL3_CHECK();
	}
}}}
