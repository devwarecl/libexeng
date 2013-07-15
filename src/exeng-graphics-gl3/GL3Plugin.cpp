/**
 * @file GL3Plugin.cpp
 * @brief Implementation of the plugin
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "GL3Plugin.hpp"
#include "GL3GraphicsDriverFactory.hpp"

#include <exeng/Root.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <iostream>

namespace exeng {
namespace graphics {
namespace gl3 {

GL3Plugin::GL3Plugin() : root(nullptr), factory(nullptr) {
    std::cout << "GL3Plugin::GL3Plugin()" << std::endl;
    this->factory = new GL3GraphicsDriverFactory();
}


GL3Plugin::~GL3Plugin() {
    this->terminate();
    
    if (this->factory != nullptr) {
        delete this->factory;
    }
    
    std::cout << "GL3Plugin::~GL3Plugin()" << std::endl;
}


std::string GL3Plugin::getName() const {
    return "OpenGL 3 Graphics Driver";
}


std::string GL3Plugin::getDescription() const {
    return "Graphics driver implemented using the OpenGL 3 Core Profile API.";
}


Version GL3Plugin::getVersion() const {
    return Version(0, 0, 1, 1);
}


void GL3Plugin::initialize(Root *root) {
    if (this->root != nullptr) {
        throw std::runtime_error("GL3Plugin::initialize: Can't "
                                 "initialize the plugin if already been "
                                 "initialized.");
    } else {
        this->root = root;
        this->root->getGraphicsManager()->addDriverFactory(this->factory);
    }
    
    std::cout << "done." << std::endl;
}


void GL3Plugin::terminate() {
    if (this->root == nullptr) {
        throw std::runtime_error("GL3Plugin::terminate: Can't "
                                 "terminate the plugin if has not been "
                                 "initialized.");
    } else {
        this->root->getGraphicsManager()->removeDriverFactory(this->factory);
        this->root = nullptr;
    }
    
    std::cout << "done." << std::endl;
}

GL3Plugin *currentPlugin = nullptr;
}
}
}

// EXENG_EXPORT_PLUGIN(exeng::graphics::gl3::GL3Plugin)

extern "C" { 
	exeng::system::Plugin*                             
	EXENG_CALLCONV ExengGetPluginObject() {                
		if (exeng::graphics::gl3::currentPlugin == nullptr) {
			exeng::graphics::gl3::currentPlugin = new exeng::graphics::gl3::GL3Plugin();
		}
		return exeng::graphics::gl3::currentPlugin;
	}
}

#if defined (EXENG_WINDOWS)
#  if defined (EXENG_32)
#    pragma comment (linker, "/export:ExengGetPluginObject=_ExengGetPluginObject")
#  elif defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#  endif
#endif 
