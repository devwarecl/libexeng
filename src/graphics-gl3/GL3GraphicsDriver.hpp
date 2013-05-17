
#ifndef __GL3_GRAPHICSDRIVER_HPP__
#define __GL3_GRAPHICSDRIVER_HPP__


#include <memory>
#include <exeng/graphics/GraphicsDriver.hpp>

#include "GL3Texture.hpp"
#include "GL3VertexBuffer.hpp"
#include "GL3IndexBuffer.hpp"
#include "GL3Screen.hpp"

namespace exeng {
    namespace graphics {
        namespace gl3 {
            /**
             * @brief GraphicsDriver implemented using OpenGL 3.x
             */
            class GL3GraphicsDriver : public GraphicsDriver {
            public:  
                GL3GraphicsDriver();
                
                virtual ~GL3GraphicsDriver();
                
                virtual void beginScene(const Color &color, ClearFlags::Enum flags = ClearFlags::Color | ClearFlags::Depth) ;
                
                virtual void endScene() ;
                
                virtual void setVertexBuffer(const VertexBuffer* vertexBuffer) ;
                
                virtual void setIndexBuffer(const IndexBuffer* indexBuffer) ;
                
                virtual const VertexBuffer* getVertexBuffer() const ;
                
                virtual const IndexBuffer* getIndexBuffer() const ;
                
                virtual void setMaterial(const Material* Mat) ;
                
                virtual const Material* getMaterial() const ;
                
                virtual VertexBuffer* createVertexBuffer(const VertexFormat &vertexFormat, int vertexCount) ;
                
                virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, int IndexCount  ) ;
                
                virtual Texture* createTexture(TextureType TextureType, const exeng::math::Vector3f& TextureSize) ;
                
                virtual void setTransform(Transform transform, const exeng::math::Matrix4f& matrix) ;
                
                virtual exeng::math::Matrix4f getTransform(Transform transform) ;
                
                virtual void setViewport(const exeng::math::Rectf& viewport) ;
                
                virtual exeng::math::Rectf getViewport() const ;
                
                virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount) ;
                
                Screen* getScreen() const;
                
            private:
                struct Private;
                std::unique_ptr<Private> impl;
            };
        }    
    }
}

#endif
