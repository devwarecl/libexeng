/**
 * @file GraphicsDriverFactoryGL3.hpp
 * @brief Definition of the graphics driver factory intetface
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_GL3_GL3GRAPHICSDRIVERFACTORY_HPP__
#define __EXENG_GRAPHICS_GL3_GL3GRAPHICSDRIVERFACTORY_HPP__

#include <list>
#include <xe/gfx/GraphicsManager.hpp>

namespace xe { namespace gfx { namespace gl3 {

    class GraphicsDriverGL3;
    class GraphicsDriverFactoryGL3 : public IGraphicsDriverFactory {
    public:
        GraphicsDriverFactoryGL3();
        virtual ~GraphicsDriverFactoryGL3();
        
        virtual GraphicsDriverInfo getDriverInfo() const override;
        virtual std::unique_ptr<GraphicsDriver> create() override;
    };
}}}

#endif  //__EXENG_GRAPHICS_GL3_GL3GRAPHICSDRIVERFACTORY_HPP__
