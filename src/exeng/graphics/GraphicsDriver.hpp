/**
 * @file 
 * @brief GraphicsDriver class API and support structures and enumerations.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef exeng_graphics_graphicsdriver_hpp
#define exeng_graphics_graphicsdriver_hpp

#include <string>
#include <vector>

#include <exeng/Object.hpp>
#include <exeng/TFlags.hpp>
#include <exeng/math/TBoundary.hpp>
#include <exeng/math/TMatrix.hpp>

#include <exeng/graphics/Color.hpp>
#include <exeng/graphics/PixelFormat.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexBuffer.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/Screen.hpp>
#include <exeng/graphics/Primitive.hpp>

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
         * @brief 
         */
        namespace ClearFlags {
            enum _Enum {
                Color = 0x00000001,
                Depth = 0x00000002,
                Stencil  = 0x00000004
            };
            
            typedef TFlags<_Enum> Enum;
        }
        
        class EXENGAPI Texture;
        class EXENGAPI VertexBuffer;
        class EXENGAPI IndexBuffer;
        class EXENGAPI Material;
        
        /**
         * @brief Rasterizer rendering facility
         */
        class EXENGAPI GraphicsDriver : public Object {
        public:
            virtual ~GraphicsDriver() {}
            
            /**
             * @brief Start the rendering of a new frame, clearing the previous one
             */
            virtual void beginScene(const Color &color, ClearFlags::Enum flags = ClearFlags::Color | ClearFlags::Depth) = 0;
            
            /**
             * @brief Flip the backbuffer and the front buffer
             */
            virtual void endScene() = 0;
            
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
            virtual void setMaterial(const Material* Mat) = 0;
            
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
            virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, int IndexCount  ) = 0;
            
            /**
             * @brief Create a new texture object.
             */
            virtual Texture* createTexture(TextureType TextureType, const exeng::math::Vector3f& TextureSize) = 0;
            
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
             */
            virtual void render(exeng::graphics::Primitive::Enum primitiveType, int vertexCount) = 0;
            
            /**
             * @brief Get the current rendering screen.
             */
            Screen* getScreen() const;
        };
    }
}

#endif
