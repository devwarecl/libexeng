/**
 * @file GL3Plugin.hpp
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

    class GL3GraphicsDriverFactory;

    /**
    * @brief The GL3Plugin class
    */
    class GL3Plugin : public xe::sys::Plugin {
    public:
        GL3Plugin();
        virtual ~GL3Plugin();
        virtual std::string getName() const override;
        virtual std::string getDescription() const override;
        virtual Version getVersion() const override;
        virtual void initialize(Core *root) override;
        virtual void terminate() override;
        
    public:
        inline GL3GraphicsDriverFactory* getFactory() {
            return this->factory.get();
        }
        
    private:
        Core *root = nullptr;
        std::unique_ptr<GL3GraphicsDriverFactory> factory;
    };
}}}

#endif // __EXENG_GRAPHICS_GL3_GL3PLUGIN_HPP__
