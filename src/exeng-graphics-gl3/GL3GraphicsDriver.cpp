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


#include "GL3GraphicsDriver.hpp"
#include "GL3Debug.hpp"

#include <map>
#include <GL/glcorearb.h>
#include <GL/glfw.h>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::graphics;

namespace exeng {
    namespace graphics {
        namespace gl3 {

            GL3GraphicsDriver::GL3GraphicsDriver() {
                this->vertexBuffer = nullptr;
                this->initialized = false;
            }
            
            
            GL3GraphicsDriver::~GL3GraphicsDriver() {
            }
            
            
            void 
            GL3GraphicsDriver::initialize(const DisplayMode &displayMode) {
                // NOTE: The use of the GLFW library to implement the initialization of the
                // OpenGL 3 Driver is only temporal.
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
                
                this->initialized = true;
            }
            
            
            void 
            GL3GraphicsDriver::terminate() {
                if (this->initialized == true) {
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
                // Clears the opengl framebuffer
                GLenum clearFlags = 0L;
                
                clearFlags |= flags.getFlag(ClearFlags::Color) ? GL_COLOR_BUFFER_BIT : 0;
                clearFlags |= flags.getFlag(ClearFlags::Depth) ? GL_DEPTH_BUFFER_BIT : 0;
                
                if (!clearFlags) {
                    throw std::invalid_argument("GL3GraphicsDriver::beginScene: "
                                                "Flags must be non 0.");
                }
                
                ::glClearColor(color.red, color.green, color.blue, color.alpha);
                ::glClear(clearFlags);
            }
            
            
            void 
            GL3GraphicsDriver::endFrame() {
                ::glFlush();
            }
            
            
            void 
            GL3GraphicsDriver::setVertexBuffer(const VertexBuffer* vertexBuffer) {
                
                if (this->vertexBuffer == vertexBuffer) {
                    return;
                }
                
                if (vertexBuffer->getCreator() != this) {
                    throw std::invalid_argument("Invalid vertex buffer");
                }
                
                if (vertexBuffer->isEmpty() == true) {
                    throw std::invalid_argument("Vertex buffer can't be empty");
                }
                
                this->vertexBuffer = static_cast<const GL3VertexBuffer*>(vertexBuffer);
                
                
                GLuint name = this->vertexBuffer->getName();
                ::glBindBuffer(GL_ARRAY_BUFFER, name);
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
                                            const Matrix4f& matrix) {
            }
            
            
            void GL3GraphicsDriver::setViewport(const Rectf& viewport) {
            }
            
            
            void 
            GL3GraphicsDriver::render(Primitive::Enum primitiveType, 
                                      int vertexCount) {
            }
        }
    }
}
