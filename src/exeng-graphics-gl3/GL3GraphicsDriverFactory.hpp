/**
 * @file GL3GraphicsDriverFactory.hpp
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
#include <exeng/graphics/GraphicsManager.hpp>
#include <GLFW/glfw3.h>

namespace exeng {
namespace graphics {
namespace gl3 {

class GL3GraphicsDriver;

class GL3GraphicsDriverFactory : public IGraphicsDriverFactory {
public:
    GL3GraphicsDriverFactory();
    virtual ~GL3GraphicsDriverFactory();
    
    virtual GraphicsDriverInfo getDriverInfo() const;
    virtual GraphicsDriver* create();
    
    /**
     * @brief Get the corresponding graphics driver.
     */
    GL3GraphicsDriver* getGraphicsDriver(const GLFWwindow *window);
    
private:
    std::list<GL3GraphicsDriver*> graphicsDrivers;
};
}
}
}

#endif  //__EXENG_GRAPHICS_GL3_GL3GRAPHICSDRIVERFACTORY_HPP__
