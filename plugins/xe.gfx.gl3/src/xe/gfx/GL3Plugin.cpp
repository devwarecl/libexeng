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

#include <xe/Core.hpp>
#include <xe/Exception.hpp>
#include <xe/gfx/GraphicsManager.hpp>

namespace xe { namespace gfx { namespace gl3 {
    GL3Plugin::GL3Plugin() {
        this->factory = std::make_unique<GL3GraphicsDriverFactory>();
    }

    GL3Plugin::~GL3Plugin() {
        this->terminate();
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

    void GL3Plugin::initialize(Core *root) {
        if (this->root != nullptr) {
			EXENG_THROW_EXCEPTION("Can't initialize the plugin if already been initialized.");
        } 

        this->root = root;
        this->root->getGraphicsManager()->addDriverFactory(this->factory.get());
    }

    void GL3Plugin::terminate() {
        if (this->root == nullptr) {
            EXENG_THROW_EXCEPTION("Can't terminate the plugin if has not been initialized.");
        } 

        this->root->getGraphicsManager()->removeDriverFactory(this->factory.get());
        this->root = nullptr;
    }

    GL3Plugin *currentPlugin = nullptr;
}}}

#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::gfx::gl3::GL3Plugin)
