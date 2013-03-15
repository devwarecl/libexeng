

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include "GraphicsDriver.hpp"
#include <list>

namespace exeng
{
    namespace graphics
    {
        /**
         * @brief Base common functionality for easing the process of implementing graphics drivers
         */
        class GraphicsDriverBase : public GraphicsDriver
        {
        public:
            GraphicsDriverBase();
            
            virtual ~GraphicsDriverBase();
            
            virtual DisplayMode getDisplayMode() const;
            
            virtual math::Matrix4f getTransform(Transform::Type transform);
            
            virtual bool getFullScreenStatus() const;
            
            virtual Material getMaterial() const;
            
            virtual math::Rectf getViewport() const;
            
        protected:
            math::Matrix4f model;
            math::Matrix4f view;
            math::Matrix4f projection;
            math::Matrix4f modelView;
            
            math::Rectf viewPort;
            
            DisplayMode displayMode;
            bool fullScreen;
            
            VertexBuffer* vertexBuffer;
            IndexBuffer* indexBuffer;
            Material material;
        };
    }
}

#endif  //__EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
