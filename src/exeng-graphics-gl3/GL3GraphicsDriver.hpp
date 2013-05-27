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

#include <memory>

#include <exeng/graphics/GraphicsDriverBase.hpp>
#include <exeng/graphics/VertexFormat.hpp>

#include "GL3Texture.hpp"
#include "GL3VertexBuffer.hpp"
#include "GL3IndexBuffer.hpp"

namespace exeng {
    namespace graphics {
        namespace gl3 {
            
            /**
             * @brief GraphicsDriver implemented using OpenGL 3.x
             */
            class GL3GraphicsDriver : public GraphicsDriverBase {
            public:  
                GL3GraphicsDriver();
                
                virtual ~GL3GraphicsDriver();
                
                virtual void initialize(const DisplayMode &displayMode);
                
                virtual void terminate();
                
                virtual bool isInitialized() const;
                
                virtual void beginFrame(const Color &color, ClearFlags::Flags flags) ;
                
                virtual void endFrame();
                
                virtual void setVertexBuffer(const VertexBuffer* vertexBuffer);
                
                virtual void setIndexBuffer(const IndexBuffer* indexBuffer);
                
                virtual void setMaterial(const Material* material);
                
                virtual VertexBuffer* createVertexBuffer(const VertexFormat &vertexFormat, int vertexCount);
                
                virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, int IndexCount  );
                
                virtual Texture* createTexture(TextureType TextureType, const exeng::math::Vector3f& TextureSize);
                
                virtual void setTransform(Transform transform, const exeng::math::Matrix4f& matrix);
                
                virtual void setViewport(const exeng::math::Rectf& viewport);
                
                virtual exeng::math::Rectf getViewport() const;
                
                virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount);
                
            private:
                const GL3VertexBuffer *vertexBuffer;
                bool initialized;
            };
        }
    }
}

#endif  // __EXENG_GRAPHICS_GL3_GRAPHICSDRIVER_HPP__
