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

#include "../math/TBoundary.hpp"
#include "../math/TMatrix.hpp"

namespace exeng {
    namespace graphics {
        
        /**
         * @brief Fundamental rendering primitives
         */
        enum class Primitive {
            PointList,      //! Point lists
            LineList,       //! Line lists.
            LineStrip,      //! Line strip.
            LineLoop,       //! Line loop
            TriangleList,   //! Triangle lists
            TriangleStrip,  //! Triangle strips
            TriangleFan     //! Triangle fans
        };
        
        
        /**
         * @brief Encapsulate a display mode.
         */
        struct DisplayMode {
            DisplayMode() {}
            
            DisplayMode(const exeng::math::Size2i &size, PixelFormat format) {
                this->size = size;
                this->format = format;
                this->frequency = 0;
            }
            
            exeng::math::Size2i size;
            PixelFormat format;
            int frequency;
        };
        
        
        /**
         * @brief Framebuffer clearing flags.
         */
        enum class FrameBufferFlags { 
            ColorBuffer = 0x01,
            DepthBuffer = 0x02,
            StencilBuffer = 0x04,
            Default = ColorBuffer | DepthBuffer | StencilBuffer
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
         * @brief Event data.
         */
        struct EventData {
            int type;
            void *data;

            EventData() : type(0), data(NULL) {}
        };
        
        
        /**
         * @brief 
         */
        class EXENGAPI IEvtHandler {
        public:
            virtual ~IEvtHandler() {}
            virtual void handleEvent(const Object& Sender, EventData& Data) = 0;
        };
        

        /**
         * @brief Array of display modes
         */
        typedef std::vector<DisplayMode> DisplayModeVector;
        

        /**
         * @brief Screen modes
         */
        enum class ScreenMode {
            Windowed,	//! Windowed mode
            FullScreen	//! Fullscreen mode
        };

        
        class EXENGAPI Texture;
        class EXENGAPI VertexBuffer;
        class EXENGAPI IndexBuffer;
        class EXENGAPI Material;
        
        /**
         * @brief GraphicsDriver
         */
        class EXENGAPI GraphicsDriver : public Object {
        public:
            virtual ~GraphicsDriver() {}
            
            /**
             * @brief Enumerate the supported display modes
             */
            virtual DisplayModeVector enumDisplayModes() const = 0;
            
            /**
             * @brief Create, and initialize the main window.
             */
            virtual void initialize() = 0;
            
            /**
             * @brief 
             */
            virtual void initialize(const DisplayMode& displayMode, ScreenMode::Type screenMode) = 0;

            /**
             * @brief 
             */
            virtual void terminate() = 0;

            /**
             * @brief Set the currently display mode.
             * Note that one must call later SetFullScreenStatus (if the window is in windowed mode)
             */
            virtual void setDisplayMode(const DisplayMode& Mode) = 0;
            
            /**
             * @brief  Get the currently 
             */
            virtual DisplayMode getDisplayMode() const = 0;
            
            /**
             * @brief Set the fullscreen status.
             */
            virtual void setFullScreenStatus(bool Status) = 0;
            
            /**
             * @brief Get the fullscreen status
             */
            virtual bool getFullScreenStatus() const = 0;
            
            /**
             * @brief Check pending events, and processes them. 
             */
            virtual void pollEvents() = 0;
            
            /**
             * @brief Register a new event handler for the system
             */
            virtual void addEvtHandler(IEvtHandler& handler) = 0;
            
            /**
             * @brief Unregister the specified event handler, if exist.
             */
            virtual void removeEvtHandler(IEvtHandler& handler) = 0;
            
            /**
             * @brief Start the rendering of a new frame, clearing the previous one
             */
            virtual void beginScene(FrameBufferFlags::Type BufferFlags = FrameBufferFlags::Default) = 0;
            
            /**
             * @brief Flip the backbuffer and the front buffer
             */
            virtual void endScene() = 0;
            
            /**
             * @brief Set the currently used vertex buffer
             */
            virtual void setVertexBuffer(const VertexBuffer* In) = 0;
            
            /**
             * @brief Set the current index buffer
             */
            virtual void setIndexBuffer(const IndexBuffer* In) = 0;
            
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
            virtual void setMaterial(const Material& Mat) = 0;
            
            /**
             * @brief Get the currently used material
             */
            virtual Material getMaterial() const = 0;
            
            /**
             * @brief Create a new hardware-based vertex buffer. 
             */
            virtual VertexBuffer* createVertexBuffer( const VertexBufferFormat &VertexFormat, int VertexCount ) = 0;
            
            /**
             * @brief Like CreateVertexBuffer, create a new hardware based index buffer.
             */
            virtual IndexBuffer* createIndexBuffer( IndexBufferFormat::Type IndexFormat, int IndexCount  ) = 0;
            
            /**
             * @brief Create a new texture object.
             */
            virtual Texture* createTexture(TextureType TextureType, const math::Vector3f& TextureSize) = 0;
            
            /**
             * @brief Set the current transformation matrix
             */
            virtual void setTransform(Transform::Type transform, const math::Matrix4f& matrix) = 0;
            
            /**
             * @brief Get the current transformation applied on the device.
             */
            virtual math::Matrix4f getTransform(Transform::Type transform) = 0;
            
            /**
             * @brief Set the area of the screen that can be rendered
             */
            virtual void setViewport(const math::Rectf& viewport) = 0;
            
            /**
             * @brief Return the currently setted viewport.
             */
            virtual math::Rectf getViewport() const = 0;
            
            /**
             * @brief Render, using the specified primitive and the currently setted material, 
             * vertex and index buffers, if any. 
             */
            virtual void render(Primitive PrimitiveType, int PrimitiveCount) = 0;
        };
    }
}

#endif
