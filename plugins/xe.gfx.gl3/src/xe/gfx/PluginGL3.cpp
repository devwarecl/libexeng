/**
 * @file PluginGL3.cpp
 * @brief Implementation of the plugin
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include "PluginGL3.hpp"
#include "GraphicsDriverFactoryGL3.hpp"

#include <xe/Core.hpp>
#include <xe/Exception.hpp>
#include <xe/gfx/GraphicsManager.hpp>

namespace xe { namespace gfx { namespace gl3 {
    PluginGL3::PluginGL3() {
        this->factory = std::make_unique<GraphicsDriverFactoryGL3>();
    }

    PluginGL3::~PluginGL3() {
        this->terminate();
    }

    std::string PluginGL3::getName() const {
        return "OpenGL 3 Graphics Driver";
    }

    std::string PluginGL3::getDescription() const {
        return "Graphics driver implemented using the OpenGL 3 Core Profile API.";
    }

    Version PluginGL3::getVersion() const {
        return Version(0, 0, 1, 1);
    }

    void PluginGL3::initialize(Core *root) {
        if (this->root != nullptr) {
			EXENG_THROW_EXCEPTION("Can't initialize the plugin if already been initialized.");
        } 

        this->root = root;
        this->root->getGraphicsManager()->addDriverFactory(this->factory.get());
    }

    void PluginGL3::terminate() {
        if (this->root == nullptr) {
            EXENG_THROW_EXCEPTION("Can't terminate the plugin if has not been initialized.");
        } 

        this->root->getGraphicsManager()->removeDriverFactory(this->factory.get());
        this->root = nullptr;
    }

    PluginGL3 *currentPlugin = nullptr;
}}}

#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::gfx::gl3::PluginGL3)
