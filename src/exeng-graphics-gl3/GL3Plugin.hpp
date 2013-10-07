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

#include <exeng/system/Plugin.hpp>

namespace exeng { namespace graphics { namespace gl3 {

class GL3GraphicsDriverFactory;

/**
 * @brief The GL3Plugin class
 */
class GL3Plugin : public exeng::system::Plugin {
public:
    GL3Plugin();
    virtual ~GL3Plugin();
    virtual std::string getName() const;
    virtual std::string getDescription() const;
    virtual Version getVersion() const;
    virtual void initialize(Root *root);
    virtual void terminate();
    
public:
    inline GL3GraphicsDriverFactory* getFactory() {
        return this->factory;
    }
    
private:
    Root *root;
    GL3GraphicsDriverFactory *factory;
};

extern GL3Plugin *currentPlugin;

}}}

#endif // __EXENG_GRAPHICS_GL3_GL3PLUGIN_HPP__
