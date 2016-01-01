/**
 * @file GL3GraphicsDriverFactory.cpp
 * @brief Implementation of the graphics driver factory
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "GL3.hpp"
#include "GL3GraphicsDriver.hpp"
#include "GL3GraphicsDriverFactory.hpp"

namespace xe { namespace gfx { namespace gl3 {
    GL3GraphicsDriverFactory::GL3GraphicsDriverFactory() {}
    GL3GraphicsDriverFactory::~GL3GraphicsDriverFactory() {}

    GraphicsDriverInfo GL3GraphicsDriverFactory::getDriverInfo() const 
    {
        GraphicsDriverInfo info;
        
        info.name = "OpenGL 3 Core Profile Graphics Driver";
        info.version = Version(0, 0, 0, 1);
        info.type = DriverType::Hardware;
        info.shadingLanguages = {{ShaderLanguage::GLSL, Version(3, 3, 0, 0)}};
        
        return info;
    }

    std::unique_ptr<GraphicsDriver> GL3GraphicsDriverFactory::create() 
    {
		return std::unique_ptr<GraphicsDriver>(new GL3GraphicsDriver());
    }
}}}
