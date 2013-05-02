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

#include "../Object.hpp"
#include "../math/TBoundary.hpp"
#include "../math/TMatrix.hpp"
#include "PixelFormat.hpp"
#include "VertexFormat.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "Screen.hpp"

namespace exeng {
    namespace graphics {
        
        /**
         * @brief Fundamental rendering primitives
         */
        enum class Primitive {
            PointList       = 0x00001001,   //! Point lists
            
            LineList        = 0x00002001,   //! Line lists.
            LineStrip       = 0x00002002,   //! Line strip.
            LineLoop        = 0x00002003,   //! Line loop
            
            TriangleList    = 0x00004001,   //! Triangle lists
            TriangleStrip   = 0x00004002,   //! Triangle strips
            TriangleFan     = 0x00004003,   //! Triangle fans
            
            // Group markers. Used for check if a given primitive 
            // is a point, line or triangle.
            Point           = 0x00001000,
            Line            = 0x00002000,
            Triangle        = 0x00004000
        };
        
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
        enum class ClearFlags {
            Color = 0x00000001,
            Depth = 0x00000002,
            Stencil  = 0x00000004
        };
        
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
            virtual void beginScene(const Color &color, ClearFlags flags = ClearFlags::Color|ClearFlags::Depth) = 0;
            
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
            virtual VertexBuffer* getVertexBuffer() const = 0;
            
            /**
             * @brief Get the currently used index buffer.
             */
            virtual IndexBuffer* getIndexBuffer() const = 0;
            
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
            virtual void render(Primitive primitiveType, int vertexCount) = 0;
            
            /**
             * @brief Get the current rendering screen.
             */
            Screen* getScreen() const;
        };
    }
}

#endif
