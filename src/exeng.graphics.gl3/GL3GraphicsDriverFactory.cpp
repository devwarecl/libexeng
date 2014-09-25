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

namespace exeng { namespace graphics { namespace gl3 {

    GL3GraphicsDriverFactory::GL3GraphicsDriverFactory() {}

    GL3GraphicsDriverFactory::~GL3GraphicsDriverFactory() {}

    GraphicsDriverInfo GL3GraphicsDriverFactory::getDriverInfo() const {
        GraphicsDriverInfo info;
        
        info.name = "OpenGL 3 core profile graphics driver";
        info.version = Version(0, 0, 0, 1);
        info.hardware = true;
        info.supportsVertexShaders = true;
        info.supportsPixelShader = true;
        info.supportsGeometryShaders = true;
        
        return info;
    }


    GraphicsDriver* GL3GraphicsDriverFactory::create() {
        auto *driver = new GL3GraphicsDriver();
        this->graphicsDrivers.push_back(driver);
        return driver;
    }


    GL3GraphicsDriver* GL3GraphicsDriverFactory::getGraphicsDriver(const GLFWwindow *window) {
        auto &drivers = this->graphicsDrivers;
        auto pos = std::find_if(drivers.begin(), drivers.end(), [window](const GL3GraphicsDriver *driver) {
            return driver->getGLFWwindow() == window;
        });
        
        assert(pos != drivers.end());
        
        return *pos;
    }
}}}
