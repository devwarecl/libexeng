/**
 * @file PluginGL3.hpp
 * @brief Definition of the plugin implementation
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GL3_GL3PLUGIN_HPP__
#define __EXENG_GRAPHICS_GL3_GL3PLUGIN_HPP__

#include <memory>
#include <xe/sys/Plugin.hpp>

namespace xe { namespace gfx { namespace gl3 {

    class GraphicsDriverFactoryGL3;

    /**
    * @brief The PluginGL3 class
    */
    class PluginGL3 : public xe::sys::Plugin {
    public:
        PluginGL3();
        virtual ~PluginGL3();
        virtual std::string getName() const override;
        virtual std::string getDescription() const override;
        virtual Version getVersion() const override;
        virtual void initialize(Core *root) override;
        virtual void terminate() override;
        
    public:
        inline GraphicsDriverFactoryGL3* getFactory() {
            return this->factory.get();
        }
        
    private:
        Core *root = nullptr;
        std::unique_ptr<GraphicsDriverFactoryGL3> factory;
    };
}}}

#endif // __EXENG_GRAPHICS_GL3_GL3PLUGIN_HPP__
