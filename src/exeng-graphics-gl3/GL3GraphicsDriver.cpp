
#include "GL3GraphicsDriver.hpp"

#include <map>
#include <boost/ptr_container/ptr_list.hpp>

#define GLCOREARB_PROTOTYPES
#include <GL/glcorearb.h>

using namespace exeng;
using namespace exeng::math;

namespace exeng {
    namespace graphics {
        namespace gl3 {
            
            struct GL3GraphicsDriver::Private {
                boost::ptr_list<Object> objects;
                
                const VertexBuffer *vertexBuffer;
                const IndexBuffer *indexBuffer;
                const Material *material;
                
                std::map<Transform, Matrix4f> transforms;
                
                Private() {
                    this->vertexBuffer = nullptr;
                    this->indexBuffer = nullptr;
                    this->material = nullptr;
                    
                    this->transforms[Transform::World].identity();
                }
            };
            
            
            GL3GraphicsDriver::GL3GraphicsDriver() : impl(new GL3GraphicsDriver::Private()) {
            }
            
            
            GL3GraphicsDriver::~GL3GraphicsDriver() {
            }
            
            
            void GL3GraphicsDriver::beginScene(const Color &color, ClearFlags::Enum flags) {
                // Clears the opengl framebuffer
                GLenum clearFlags = 0L;
                
                clearFlags |= flags.getFlag(ClearFlags::Color) ? GL_COLOR_BUFFER_BIT : 0;
                clearFlags |= flags.getFlag(ClearFlags::Depth) ? GL_DEPTH_BUFFER_BIT : 0;
                
                if (!clearFlags) {
                    throw std::invalid_argument("beginScene: Flags must be non 0.");
                }
                
                ::glClearColor(color.red, color.green, color.blue, color.alpha);
                ::glClear(clearFlags);
            }
            
            
            void GL3GraphicsDriver::endScene() {
                ::glFlush();
            }
            
            
            void GL3GraphicsDriver::setVertexBuffer(const VertexBuffer* vertexBuffer) {
                this->impl->vertexBuffer = vertexBuffer;
                
                //! TODO: Bind buffer data.
            }
            
            
            void GL3GraphicsDriver::setIndexBuffer(const IndexBuffer* indexBuffer) {
                this->impl->indexBuffer = indexBuffer;
            }
            
            
            const VertexBuffer* GL3GraphicsDriver::getVertexBuffer() const {
                return this->impl->vertexBuffer;
            }
            
            
            const IndexBuffer* GL3GraphicsDriver::getIndexBuffer() const {
                return this->impl->indexBuffer;
            }
            
            
            void GL3GraphicsDriver::setMaterial(const Material* material) {
                this->impl->material = material;
            }
            
            
            const Material* GL3GraphicsDriver::getMaterial() const {
                return this->impl->material;
            }
            
            
            VertexBuffer* GL3GraphicsDriver::createVertexBuffer(const VertexFormat &vertexFormat, int vertexCount) {
                return nullptr;
            }
            
            
            IndexBuffer* GL3GraphicsDriver::createIndexBuffer( IndexFormat IndexFormat, int IndexCount  ) {
                return nullptr;
            }
            
            
            Texture* GL3GraphicsDriver::createTexture(TextureType TextureType, const Vector3f& TextureSize) {
                return nullptr;
            }
            
            
            void GL3GraphicsDriver::setTransform(Transform transform, const Matrix4f& matrix) {
                
            }
            
            
            Matrix4f GL3GraphicsDriver::getTransform(Transform transform) {
                return Matrix4f();
            }
            
            
            void GL3GraphicsDriver::setViewport(const Rectf& viewport) {
                
            }
            
            Rectf GL3GraphicsDriver::getViewport() const {
                return Rectf();
            }
            
            
            void GL3GraphicsDriver::render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount) {
                
            }
            
            
            Screen* GL3GraphicsDriver::getScreen() const {
                return nullptr;
            }
        }
    }
}
