/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include "GraphicsDriver.hpp"
#include <list>

namespace exeng {
    namespace graphics {
        /**
         * @brief Base common functionality for easing the process of implementing graphics drivers
         */
        class GraphicsDriverBase : public GraphicsDriver {
        public:
            GraphicsDriverBase();
            
            virtual ~GraphicsDriverBase();
            
            virtual DisplayMode getDisplayMode() const;
            
            virtual exeng::math::Matrix4f getTransform(Transform::Type transform);
            
            virtual bool getFullScreenStatus() const;
            
            virtual Material getMaterial() const;
            
            virtual exeng::math::Rectf getViewport() const;
            
        protected:
            exeng::math::Matrix4f model;
            exeng::math::Matrix4f view;
            exeng::math::Matrix4f projection;
            exeng::math::Matrix4f modelView;
            
            exeng::math::Rectf viewPort;
            
            DisplayMode displayMode;
            bool fullScreen;
            
            VertexBuffer* vertexBuffer;
            IndexBuffer* indexBuffer;
            Material material;
        };
    }
}

#endif  //__EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
