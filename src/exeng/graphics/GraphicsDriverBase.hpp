/**
 * @file GraphicsDriverBase.hpp
 * @brief Defines the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include <exeng/graphics/GraphicsDriver.hpp>
#include <boost/ptr_container/ptr_list.hpp>


namespace exeng {
    namespace graphics {
        
        /**
         * @brief Base common functionality for easing the process 
         * of implementing graphics drivers
         */
        class GraphicsDriverBase : public GraphicsDriver {
        public:
            GraphicsDriverBase();
            
            virtual ~GraphicsDriverBase();
            
            virtual exeng::math::Matrix4f getTransform( Transform transform );
            
            virtual exeng::math::Rectf getViewport( ) const;
            
            virtual const exeng::graphics::Material* getMaterial( ) const;
            
            virtual VertexBuffer* createVertexBuffer( const VertexFormat &vertexFormat, int vertexCount );
            
            virtual IndexBuffer* createIndexBuffer( IndexFormat IndexFormat, int IndexCount );
            
            virtual void notifyDestruction(Object *object);
            
        protected:
            const exeng::graphics::Material* material;
            boost::ptr_list<Object> objects;
            
            exeng::math::Matrix4f model;
            exeng::math::Matrix4f view;
            exeng::math::Matrix4f projection;
            exeng::math::Matrix4f modelView;
            exeng::math::Rectf viewport;
        };
    }
}

#endif  // __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
